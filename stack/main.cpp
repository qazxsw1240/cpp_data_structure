#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <exception>

#include "array_stack.cpp"

const std::string DELIMITERS = " \t\r\n";
const std::string OPERATORS = "()+-*/";

enum class token_type {
    number,
    function
};

struct token {
    token_type m_type;
    std::string m_value;

    token();

    token(token_type type, std::string value);

    std::size_t get_priority() const;
};

token::token() : m_type(token_type::number),
                 m_value(std::string()) {}

token::token(token_type type, std::string value) : m_type(type),
                                                   m_value(std::move(value)) {}

std::size_t token::get_priority() const {
    if (this->m_type == token_type::number)
        return static_cast<std::size_t>(-1);
    // 괄호가 연산자보다 우선순위가 낮은 것은 알고리즘 동작 중 연산자가 스택에 추가될 때
    // 괄호가 연산자로서 꺼내지는 것을 방지하기 위함입니다.
    if (this->m_value == "(" || this->m_value == ")")
        return 0;
    if (this->m_value == "+" || this->m_value == "-")
        return 1;
    if (this->m_value == "*" || this->m_value == "/")
        return 2;
    return static_cast<std::size_t>(-1);
}

class tokenizer {
    /**
     * 수식으로 표현된 문자열
     */
    const std::string _expr;
    /**
     * 문자열의 길이
     */
    const std::size_t _len;
    /*
     * 탐색을 시작할 현재 인덱스 값
     */
    std::size_t _pos;

    /**
     * 제공된 위치에서 가까운 공백 문자가 나타나지 않는 가장 작은 인덱스의 값을 반환합니다.
     * @param pos 탐색을 시작할 위치
     * @returns 공백 문자가 나타나지 않는 가장 가까운 인덱스 값
     */
    std::size_t skip_delimiters(std::size_t pos) const;

    /**
     * 제공된 위치에서 가까운 숫자 문자가 나타나지 않는 가장 작은 인덱스의 값을 반환합니다.
     * @param pos 탐색을 시작할 위치
     * @returns 숫자 문자가 나타나지 않는 가장 가까운 인덱스 값
     */
    std::size_t read_digits(std::size_t pos) const;

public:
    /**
     * 토큰 추출기를 초기화합니다.
     * @param expression 토큰을 추출할 수식 문자열
     */
    explicit tokenizer(std::string expression);

    /**
     * 토큰을 추출해서 참조 매개변수에 할당합니다.
     * 토큰이 존재하면 @c true, 존재하지 않으면 @c false를 반환합니다.
     * @param value 값을 할당할 참조 매개변수
     * @return 토큰이 존재하면 @c true, 존재하지 않으면 @c false
     */
    bool next(token &value);
};

std::size_t tokenizer::skip_delimiters(std::size_t pos) const {
    while (pos < this->_len) {
        if (DELIMITERS.find(this->_expr[pos]) == std::string::npos)
            break;
        ++pos;
    }
    return pos;
}

std::size_t tokenizer::read_digits(std::size_t pos) const {
    while (pos < this->_len) {
        if (!std::isdigit(this->_expr[pos]))
            break;
        ++pos;
    }
    return pos;
}

tokenizer::tokenizer(std::string expression) : _expr(std::move(expression)),
                                               _len(this->_expr.length()),
                                               _pos(0) {}

bool tokenizer::next(token &value) {
    this->_pos = this->skip_delimiters(this->_pos);
    if (this->_pos >= this->_len)
        return false;
    if (OPERATORS.find(this->_expr[this->_pos]) != std::string::npos) {
        value.m_type = token_type::function;
        value.m_value = this->_expr.substr(this->_pos, 1);
        ++this->_pos;
        return true;
    }
    const std::size_t start = this->_pos;
    this->_pos = this->read_digits(start);
    if (start == this->_pos)
        throw std::runtime_error("invalid character in expression.");
    value.m_type = token_type::number;
    value.m_value = this->_expr.substr(start, this->_pos - start);
    return true;
}

std::vector<token> convert_rpn(const std::string &expression) {
    // Simplified Shunting Yard Algorithm
    // 1.   토큰이 피연산자(숫자)면 바로 넘긴다.
    // 2.   토큰이 연산자면 우선순위가 같거나 높은 연산자를 스택에서 차례대로 꺼내고,
    //      해당 토큰을 스택에 저장한다.
    // 3.   토큰이 여는 괄호면 스택에 저장한다.
    // 4.   토큰이 닫는 괄호면 스택에서 여는 괄호를 찾을 때까지 연산자를 꺼낸다.
    // 4-1. 만약 스택이 빌 때까지 여는 괄호를 찾지 못했다면 괄호의 짝이 맞지 않는 것이다.
    // 5.   토큰이 이제 없다면 스택에서 연산자를 차례로 꺼낸다.
    // 5-1. 만약 스택에 괄호가 남아있다면 괄호의 짝이 맞지 않는 것이다.
    array_stack<token> token_stack(expression.length());
    tokenizer tokenizer(expression);
    std::vector<token> tokens;
    tokens.reserve(expression.length());
    token t;
    while (tokenizer.next(t)) {
        if (t.m_type == token_type::number) {
            tokens.emplace_back(t);
        } else if (t.m_value == "(") {
            token_stack.push(t);
        } else if (t.m_value == ")") {
            token inner_token;
            while (token_stack.pop(inner_token) && inner_token.m_value != "(")
                tokens.emplace_back(inner_token);
            if (inner_token.m_value != "(")
                throw std::runtime_error("invalid parenthesis pair in expression.");
        } else {
            const std::size_t priority = t.get_priority();
            token inner_token;
            while (token_stack.peek(inner_token)) {
                if (inner_token.get_priority() < priority)
                    break;
                token_stack.pop(inner_token);
                tokens.emplace_back(inner_token);
            }
            token_stack.push(t);
        }
    }
    while (token_stack.pop(t)) {
        if (t.m_value == "(")
            throw std::runtime_error("invalid parenthesis pair in expression.");
        tokens.emplace_back(t);
    }
    return tokens;
}

int evaluate_rpn(const std::vector<token> &tokens) {
    int result = 0;
    array_stack<int> token_stack(tokens.size());
    for (const token &t: tokens) {
        if (t.m_type == token_type::number) {
            token_stack.push(std::stoi(t.m_value));
        } else {
            if (token_stack.size() < 2)
                throw std::runtime_error("invalid number in expression.");
            int left, right;
            token_stack.pop(right);
            token_stack.pop(left);
            if (t.m_value == "+") {
                result = left + right;
            } else if (t.m_value == "-") {
                result = left - right;
            } else if (t.m_value == "*") {
                result = left * right;
            } else if (t.m_value == "/") {
                result = left / right;
            } else {
                throw std::runtime_error("invalid operator in expression.");
            }
            token_stack.push(result);
        }
    }
    if (token_stack.size() != 1)
        throw std::runtime_error("invalid number in expression.");
    token_stack.pop(result);
    return result;
}

int main(int, char **) {
    const std::vector<std::string> expressions{
            "(4 - 19) * (7 + 19) + 19 * (7 - 4 + 19)",
            "3 * 8 + 4",
            "4 - 2 * (6 - 3) / (3 * (11 - 3))",
            "72 / (12 - 6)",
            "1 * 1 * 1 * ((1 * 1) *" // error
    };
    for (const std::string &expression: expressions) {
        try {
            const std::vector<token> tokens = convert_rpn(expression);
            std::cout << "converted: ";
            for (const token &token: tokens)
                std::cout << token.m_value << ' ';
            std::cout << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
