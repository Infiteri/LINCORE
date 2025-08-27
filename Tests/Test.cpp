#include "Test.h"
#include "Core/Logger.h"
#include "Core/Window.h"
#include "TriangleTest.h"
#include <glad/glad.h>
#include <iostream>
#include <memory>

namespace Core
{
    TestManager::~TestManager()
    {
        for (auto t : tests)
            delete t;

        tests.clear();
    }

    void TestManager::SetupWindow()
    {
        WindowConfiguration config;
        config.Width = 1280;
        config.Height = 720;
        config.Title = "Tests";

        window = std::make_shared<Window>(config);
    }

    void TestManager::AddTest(Test *test) { tests.push_back(test); }

    int TestMain()
    {
        Core::Logger::Init();
        TestManager testManager;
        testManager.SetupWindow();
        testManager.AddTest(new EBOTest());

        testManager.AddTest(new VBOTest());
        gladLoadGL();
        while (!testManager.GetWindow()->HasCloseRequest())
        {
            for (auto &test : testManager.GetTests())
            {
                glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                std::string reason;
                if (!test->Run(reason))
                {
                    CE_ERROR("Test failed with reason");
                    CE_ERROR(reason.c_str());
                    reason.clear();
                }

                testManager.GetWindow()->Update();
                std::cin.get();
            }

            std::cin.get();
            testManager.GetWindow()->Update();
            testManager.GetTests().clear();
        }

        return 0;
    }
} // namespace Core

int main() { return Core::TestMain(); }
