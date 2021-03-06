//
//  test-utils.c
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "test-utils.h"

#include <string.h>
#include <assert.h>

char* data_to_hex(uint8_t* in, size_t insz)
{
  char* out = malloc(insz * 2 + 1);
  uint8_t* pin = in;
  const char * hex = "0123456789abcdef";
  char* pout = out;
  for(; pin < in + insz; pout += 2, pin++){
    pout[0] = hex[(*pin>>4) & 0xF];
    pout[1] = hex[ *pin     & 0xF];
  }
  pout[0] = 0;
  return out;
}

bool hex_digit_to_bin(const char hex, char *out) {
	if (out == NULL)
		return false;

	if (hex >= '0' && hex <= '9') {
		*out = hex - '0';
	} else if (hex >= 'A' && hex <= 'F') {
		*out = hex - 'A' + 10;
	} else if (hex >= 'a' && hex <= 'f') {
		*out = hex - 'a' + 10;
	} else {
		return false;
	}

	return true;
}

size_t hex_to_data(const char *hex, uint8_t **out) {
	if (hex == NULL || *hex == '\0') {
        *out = NULL;
		return 0;
    }
    if (out == NULL) {
        return 0;
    }

	size_t len = strlen(hex);
	if (len % 2 != 0)
		return 0;
	len /= 2;

	*out = malloc(len);
	for (size_t i = 0; i < len; i++) {
  	char b1;
  	char b2;
		if (!hex_digit_to_bin(hex[i * 2], &b1) || !hex_digit_to_bin(hex[i * 2 + 1], &b2)) {
			return 0;
		}
		(*out)[i] = (b1 << 4) | b2;
	}
	return len;
}

bool equal_strings(const char* a, const char* b) {
  return strcmp(a, b) == 0;
}

void test_hex() {
  char* hex = "000110ff";
  uint8_t* out;
  size_t len = hex_to_data(hex, &out);
  char* reout = data_to_hex(out, len);
  assert(equal_strings(hex, reout));
  free(out);
  free(reout);
}

// Clearly not random. Only use for tests.
void fake_random(uint8_t *buf, size_t count, void* ctx) {
  uint8_t b = 0;
  for(int i = 0; i < count; i++) {
    buf[i] = b;
    b = b + 17;
  }
}
