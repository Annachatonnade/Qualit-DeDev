#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <chrono>

// Un framework de test simpliste pour notre d�monstration
class TestFramework {
public:
    struct TestCase {
        std::string name;
        std::function<bool()> testFunction;

        TestCase(const std::string& n, std::function<bool()> func)
            : name(n), testFunction(func) {
        }
    };

    struct TestSuite {
        std::string name;
        std::vector<TestCase> testCases;

        TestSuite(const std::string& n) : name(n) {}

        void addTest(const std::string& testName, std::function<bool()> testFunction) {
            testCases.emplace_back(testName, testFunction);
        }
    };

private:
    std::vector<TestSuite> testSuites;

public:
    TestSuite& createTestSuite(const std::string& name) {
        testSuites.emplace_back(name);
        return testSuites.back();
    }

    void runTests() {
        int totalTests = 0;
        int passedTests = 0;
        auto startTime = std::chrono::high_resolution_clock::now();

        std::cout << "\n========== EX�CUTION DES TESTS ==========\n" << std::endl;

        for (auto& suite : testSuites) {
            std::cout << "Suite: " << suite.name << std::endl;

            for (auto& testCase : suite.testCases) {
                totalTests++;
                std::cout << "  Test: " << testCase.name << " - ";

                try {
                    bool result = testCase.testFunction();
                    if (result) {
                        std::cout << "R�USSITE" << std::endl;
                        passedTests++;
                    }
                    else {
                        std::cout << "�CHEC" << std::endl;
                    }
                }
                catch (const std::exception& e) {
                    std::cout << "EXCEPTION: " << e.what() << std::endl;
                }
            }

            std::cout << std::endl;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        std::cout << "========== R�SUM� DES TESTS ==========\n" << std::endl;
        std::cout << "Tests ex�cut�s : " << totalTests << std::endl;
        std::cout << "Tests r�ussis  : " << passedTests << std::endl;
        std::cout << "Tests �chou�s  : " << (totalTests - passedTests) << std::endl;
        std::cout << "Temps d'ex�cution : " << duration << " ms" << std::endl;
        std::cout << "\n=======================================" << std::endl;
    }
};

#endif // TEST_FRAMEWORK_H
