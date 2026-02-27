#include <iostream>
#include <string>

void tokenizer(char cp);
int Alphabet(char a);
std::string html;
std::string state = "data";
std::string tagname_buffer;
std::string text_buffer;
std::string attribute_key;
std::string attribute_value;
int temp = 0;
int main()
{
	std::getline(std::cin, html);
	for (int i = 0; i < html.size(); i++) {
		tokenizer(html[i]);
	}
}
void tokenizer(char cp)
{
	if (state == "data") {
		if (cp == '<') {
			state = "tag open";
		}
		else if (Alphabet(cp)) {
			state = "data";
			text_buffer += cp;
		}
	}
	else if (state == "tag open") {
		if (cp == ' ') {
			state = "attribute key";
		}
		else if (cp == '>') {
			std::cout << "tagOpen:" << tagname_buffer << "\n";
			state = "data";
		}
		else if (cp == '/') {
			std::cout << text_buffer << "\ntagClose:" << tagname_buffer << "\n";
			tagname_buffer = "";
			state = "data";
		}
		else {
			tagname_buffer += cp;
		}
	}
	else if (state == "attribute key") {
		if (cp == '=') {
			state = "attribute value";
			std::cout << "attribute key:" << attribute_key << "\n";
			attribute_key = "";
		}
		else {
			attribute_key += cp;
		}
	}
	else if (state == "attribute value") {
		if (cp == '\"' && temp == 1) {
			attribute_value += cp;
			state = "tag open";
			std::cout << "attribute value:" << attribute_value << "\n";
			attribute_value = "";
			temp = 0;
		}
		else {
			attribute_value += cp;
			temp = 1;
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