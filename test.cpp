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
	std::string state="Data";
	std::string character_buffer = "";
	std::string tagname_buffer="";
	std::ifstream inFile(file_name); //html 파일 읽기
	std::ofstream outFile("token.txt");//token 파일 쓰기
	while (inFile.get(c)) {
		if (state == "Data") {
			if (c == '<') {
				state = "Tag Open";
			}
			else if (Alphabet(c)) {
				state = "Character"; character_buffer += c;
			}
		}
		else if (state=="Tag Open") {
			if (c != '/') {
				if (c == '>') {
					outFile << "StartTag:" << tagname_buffer << "\n";
					std::cout << "StartTag:" << tagname_buffer << "\n";
					tagname_buffer = "";
					state = "Data";
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



	}	
}
int Alphabet(char a) {
	for (int i = 97; i < 123; i++) {
		if (a == char(i)) {
			return 1;
		}
		if (i == 122) {
			return 0;
		}
	}
}
