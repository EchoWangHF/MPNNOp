
#include "core/half.h"

half_t half::convertFloat2Half(const float &data) const {
  /*
  // The note can tell how convert step by step;
  uint32_t float_bit = *(uint32_t *)(&a);

  uint32_t sign_bit = (float_bit & 0x80000000) >> 16;
  uint32_t exp_bit = (((((float_bit & 0x7fffffff) >> 23) - 127) & 0x1f) + 15)
                     << 10;
  uint32_t frac_bit = ((float_bit >> 13) & 0x3ff);

  uint32_t half_bit = sign_bit | exp_bit | frac_bit;
  half_t _value = static_cast<half_t>(half_bit);
  return _value;
  */
  uint32_t float_bit = *(uint32_t *)&data;
  half_t half_data = ((float_bit & 0x7fffffff) >> 13) - (0x38000000 >> 13);
  half_data |= ((float_bit & 0x80000000) >> 16);
  return half_data;
}

float half::convertHalf2Float(const half_t &data) const {
  /*
  // The note can tell how convert step by step;
  uint32_t sign_bit = data & 0x8000;
  sign_bit = sign_bit<<16;

  uint32_t exp_bit = ((data>>10)&0x1f);
  exp_bit = exp_bit - 15 + 127;
  exp_bit = exp_bit & 0xff;
  exp_bit = exp_bit << 23;

  uint32_t frac_bit = data & 0x3ff;
  frac_bit = frac_bit << 13;

  uint32_t float_bit = sign_bit | exp_bit | frac_bit;
  float float_data = *(float *)(&float_bit);
  return float_data;
  */
  uint32_t float_bit = data;
  float_bit = ((float_bit & 0x7fff) << 13) + 0x38000000;
  float_bit |= ((data & 0x8000) << 16);
  return *(float *)&float_bit;
}
