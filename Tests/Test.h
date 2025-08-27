#pragma once

#include "Core/Window.h"
#include <memory>
#include <string>
#include <vector>
namespace Core
{
    class Test
    {
    public:
        virtual ~Test() {};
        virtual bool Run(std::string &reason)
        {
            reason = "Unimplemented run function";
            return false;
        };
    };

    class TestManager
    {
    public:
        ~TestManager();

        void SetupWindow();

        void AddTest(Test *test);
        void RunTests();

        inline std::vector<Test *> &GetTests() { return tests; };
        inline std::shared_ptr<Window> GetWindow() { return window; };

    private:
        std::vector<Test *> tests;
        std::shared_ptr<Window> window;
    };
} // namespace Core
