#include "GridBox.h"

GridBox::GridBox() {
	value = ' ';
};

char GridBox::GetValue() {
	return value;
};

void GridBox::SetValue(char newValue) {
	value = newValue;
};