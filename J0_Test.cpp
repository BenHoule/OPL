#include "JExpr.hpp"

int main(int argc, char* argv[]){
	std::cout << "---Running J0 Test Suite---\n";
	std::cout << " --args: new JNum(int)--\n";
	JExpr* plus_test = new JPlus(new JNum(2), new JNum(3));
	JExpr* mult_test = new JMult(new JNum(2), new JNum(3));
	std::cout << "1.) JPlus Print: " << plus_test->print() << "\n";
	std::cout << "2.) JMult Print: " << mult_test->print() << "\n";
	std::cout << "3.) JPlus Interp: " << (plus_test->interp())->print() << "\n";
	std::cout << "4.) JMult Interp: " << (mult_test->interp())->print() << "\n";
	delete plus_test;
	delete mult_test;
	std::cout << " --args: JNum* num--\n";
	std::cout << " --Creating JNums--\n";
	JExpr* num1 = new JNum(2), *num2 = new JNum(3);
	plus_test = new JPlus(num1, num2);
	mult_test = new JMult(num1, num2);
	std::cout << "5.) num1 Print: " << num1->print() << "\n";
	std::cout << "6.) num2 Print: " << num2->print() << "\n";
	std::cout << "7.) num1 Interp: " << (num1->interp())->print() << "\n";
	std::cout << "8.) JPlus Print: " << plus_test->print() << "\n";
	std::cout << "9.) JMult Print: " << mult_test->print() << "\n";
	std::cout << "10.) JPlus Interp: " << (plus_test->interp())->print() << "\n";
	std::cout << "11.) JMult Interp: " << (mult_test->interp())->print() << "\n";
	std::cout << "12.) All together now (JPlus * JMult): " << ((new JMult(plus_test->interp(), mult_test->interp()))->interp())->print() << "\n";
	system("pause");
	return 0;
}