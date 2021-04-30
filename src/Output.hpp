/*
 * Digital Output for Arduino.
 *
 * Copyright (c) 2021, Kupto
 *
 * Output is an abstraction over a digital output pin. It allows to drive such
 * a pin HIGH or LOW. Electrical and logical interpretation of an Output state
 * are independet and may be inverted.
 *
 * This is free software; published under the MIT license.
 * See the LICENSE file.
 */
#include <Arduino.h>
#include <inttypes.h>

#pragma once

class Output {
protected:
  const int _pin;
  const bool _invert;

public:
  enum Polarity {
    ActiveLow = 0,
    ActiveHigh,
  };
  Output(uint8_t pin, Polarity active_high = ActiveHigh)
    : _pin(pin)
    , _invert(!active_high)
  { }
  ~Output()
  { end(); }

  void begin()
  { pinMode(_pin, OUTPUT); }
  void end()
  { pinMode(_pin, INPUT); }

  void set(bool on)
  { digitalWrite(_pin, ((!!on) ^ _invert) ? HIGH : LOW); }
  void on()
  { set(true); }
  void off()
  { set(false); }

  void toggle() // Non-reentrant
  { set(!state()); }

  bool state() const // True iff active
  {
    return digitalRead(_pin) == ((_invert) ? LOW : HIGH);
  }
};
