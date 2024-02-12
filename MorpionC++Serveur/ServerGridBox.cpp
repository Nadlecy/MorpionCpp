#include "ServerGridBox.h"

ServerGridBox::ServerGridBox() {
	value = ' ';
};

char ServerGridBox::GetValue() {
	return value;
};

void ServerGridBox::SetValue(char newValue) {
	value = newValue;
};