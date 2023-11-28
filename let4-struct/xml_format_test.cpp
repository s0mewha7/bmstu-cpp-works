#include "struct-to-XML.h"
#include <gtest/gtest.h>
#include <sstream>

bool compareIgnoringWhitespace(const std::string &expected, const std::string &actual) {
    std::string expectedNoWhitespace = expected;
    expectedNoWhitespace.erase(0, expectedNoWhitespace.find_first_not_of(" \t\n"));
    expectedNoWhitespace.erase(expectedNoWhitespace.find_last_not_of(" \t\n") + 1);

    std::string actualNoWhitespace = actual;
    actualNoWhitespace.erase(0, actualNoWhitespace.find_first_not_of(" \t\n"));
    actualNoWhitespace.erase(actualNoWhitespace.find_last_not_of(" \t\n") + 1);

    return expectedNoWhitespace == actualNoWhitespace;
}

TEST(MobilePhoneTest, PrintMobilePhoneValidInput) {
    std::istringstream input("3\n1.3 1 1000.23\n2.2 0 1123\n1.0 1 100500\n");
    std::ostringstream output;

    printMobilePhone(input, output);

    std::string expected_output = "<MobilePhones>\n";
    expected_output += "\t<MobilePhone id=\"0\" weight=\"1.3\" is_broken=\"true\" price=\"1000.23\"/>\n";
    expected_output += "\t<MobilePhone id=\"1\" weight=\"2.2\" is_broken=\"false\" price=\"1123\"/>\n";
    expected_output += "\t<MobilePhone id=\"2\" weight=\"1\" is_broken=\"true\" price=\"100500\"/>\n";
    expected_output += "</MobilePhones>\n";

    ASSERT_TRUE(compareIgnoringWhitespace(expected_output, output.str()));
}

TEST(MobilePhoneTest, PrintMobilePhoneInvalidInput) {
    std::istringstream input("2\n1.3 1 1000.23\n2.2 0\n");
    std::ostringstream output;

    printMobilePhone(input, output);
    ASSERT_NE(output.str().find("Invalid input format"), std::string::npos);

}