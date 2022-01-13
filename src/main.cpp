#include <iostream>
#include <fstream>
#include <memory>
#include <stack>
#include <sstream>

int main(int argc, char* argv[])
{
    // init program

    const std::string program = [&]()
    {
        if (argc > 1)
        {
            std::ifstream stream{ argv[1] };
            return std::string{ std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>() };
        }
        else // read from terminal
        {
            std::string buf;
            std::getline(std::cin, buf);
            return buf;
        }
    }();

    // init memory

    std::unique_ptr<std::uint8_t[]> memory = std::make_unique<std::uint8_t[]>(30'000);
    std::uint8_t* head = memory.get();
    std::stack<std::size_t> stack;

    // utility function for "jumping" i forward to the next matching ']'

    auto jump_forward = [&](std::size_t& i)
    {
        std::int32_t matching = -1;

        while (matching != 0)
        {
            const char c = program[++i];

            if (c == '[')
                matching--;
            else if (c == ']')
                matching++;
        }
    };
    
    // execute program

    for (std::size_t i = 0; i < program.length(); i++)
    {
        switch (program[i])
        {
        case '>':
            head++;
            break;
        case '<':
            head--;
            break;
        case '+':
            ++*head;
            break;
        case '-':
            --*head;
            break;
        case '.':
            std::cout << *head;
            break;
        case ',':
            std::cin >> *head;
            break;
        case '[':
            stack.push(i);
            if (!*head)
                jump_forward(i);
            break;
        case ']':
            if (*head)
                i = stack.top();
            else
                stack.pop();
            break;
        default:
            break;
        }
    }
    return 0;
}
