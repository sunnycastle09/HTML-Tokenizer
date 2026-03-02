#include <iostream>
#include <fstream>

void tokenizer(std::string file_name);
int Alphabet(char a);

int main() {
	std::string a = "index.html";
	tokenizer(a);
}


void tokenizer(std::string file_name) {
	char c;
	bool is_first = true;
	std::string state = "DOCTYPE";
	std::string character_buffer = "";
	std::string tagname_buffer = "";
	std::string attribute_buffer = "";
	std::ifstream inFile(file_name); //html 파일 읽기
	std::ofstream outFile("token.txt");//token 파일 쓰기
	while (inFile.get(c)) {
		if (state == "DOCTYPE") {
			if (c != '<') {
				if (c == '>') {
					outFile << "DOCTYPE:" << character_buffer << "\n";
					std::cout << "DOCTYPE:" << character_buffer << "\n";
					character_buffer = "";
					state = "Data";
				}
				else {
					character_buffer += c;
				}
			}
		}
		else if (state == "Data") {
			if (c == '<') {
				state = "Tag Open";
			}
			else {
				state = "Character"; character_buffer += c;
			}
		}
		else if (state == "Tag Open") {
			if (c != '/') {
				if (c == '>') {
					outFile << "StartTag:" << tagname_buffer << "\n";
					std::cout << "StartTag:" << tagname_buffer << "\n";
					tagname_buffer = "";
					state = "Data";
				}
				else if (c == ' ') {
					outFile << "StartTag:" << tagname_buffer << "\n";
					std::cout << "StartTag:" << tagname_buffer << "\n";
					tagname_buffer = "";
					state = "Attribute Name";
				}
				else {
					tagname_buffer += c;
				}
			}
			else {
				state = "Tag Close";
			}
		}
		else if (state == "Tag Close") {
			if (c != '/') {// tag close에서 /문자 담기는건 피하기 위해
				if (c == '>') {
					outFile << "EndTag:" << tagname_buffer << "\n";
					std::cout << "EndTag:" << tagname_buffer << "\n";
					tagname_buffer = "";
					state = "Data";
				}
				else {
					tagname_buffer += c;
				}
			}
		}
		else if (state == "Character") {
			if (c == '<') {
				outFile << "Character:" << character_buffer << "\n";
				std::cout << "Character:" << character_buffer << "\n";
				character_buffer = "";
				state = "Tag Close";
			}
			else {
				character_buffer += c;
			}
		}
		else if (state == "Attribute Name") {
			if (c == '>') {
				outFile << "Attribute Name:" << attribute_buffer << "\n";
				std::cout << "Attribute Name:" << attribute_buffer << "\n";
				attribute_buffer = "";
				state = "Data";
			}
			else if (c != '=') {
				attribute_buffer += c;
			}
			else {
				outFile << "Attribute Name:" << attribute_buffer << "\n";
				std::cout << "Attribute Name:" << attribute_buffer << "\n";
				attribute_buffer = "";
				state = "Attribute Value";
			}
		}
		else if (state == "Attribute Value") {
			if (!is_first) {
				if (c == '\"') {
					outFile << "Attribute Value:" << attribute_buffer << "\n";
					std::cout << "Attribute Value:" << attribute_buffer << "\n";
					attribute_buffer = "";
					state = "After Attribute Value";
					is_first = true;
				}
				else {
					attribute_buffer += c;
				}
			}
			else {
				is_first = false;
			}
		}
		else if (state == "After Attribute Value") {
			if (c == '>') {
				state = "Data";
			}
			else if (c == ' ') {
				state = "Attribute Name";
			}
		}

	}
}
int Alphabet(char a) {
	if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90)) {
		return 1;
	}
	return 0;
}
