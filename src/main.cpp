#include <iostream>
#include <fstream>
#include <memory>
#include <stack>
#include <sstream>
#include <stdexcept>

constexpr std::size_t memory_size = 30'000;

static void execute(std::string_view program)
{
    // init memory

    std::unique_ptr<std::uint8_t[]> memory = std::make_unique<std::uint8_t[]>(memory_size);
    std::uint8_t* head = memory.get();
    std::stack<std::size_t> stack;

    // utility function for "jumping" i to the matching closing brace

    auto jump_forward = [&](std::size_t& i)
    {
        std::int32_t closes_needed = 1;

        while (closes_needed != 0)
        {
            if (++i >= program.length())
                throw std::runtime_error("unmatched '['");

            const char c = program[i];

            if (c == '[')
                ++closes_needed;
            else if (c == ']')
                --closes_needed;
        }
    };

    // execute program

    for (std::size_t i = 0; i < program.length(); ++i)
    {
        switch (program[i])
        {
        case '>':
            if (++head >= (memory.get() + memory_size))
                throw std::runtime_error("head out of bounds: right");
            break;
        case '<':
            if (--head < memory.get())
                throw std::runtime_error("head out of bounds: left");
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
            if (stack.empty())
                throw std::runtime_error("unmatched ']'");
            else if (*head)
                i = stack.top();
            else
                stack.pop();
            break;
        default: // ignore all other characters
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    // init program

    const std::string program = [&]()
    {
        if (argc > 1) // dump file to string
        {
            std::ifstream stream{ argv[1] };
            return std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
        }
        else // read from terminal
        {
            std::string buf;
            std::getline(std::cin, buf);
            return buf;
        }
    }();

    // execute program

    try
    {
        execute(program);
    }
    catch (std::runtime_error& e)
    {
        using namespace std::string_literals;
        std::cout << "Error: "s + e.what();
    }
    return 0;
}
