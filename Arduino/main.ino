#define SERIAL_INPUT                3
#define OUTPUT_ENABLE               2
#define STORAGE_REGISTER_CLOCK      1
#define SHIFT_REGISTER_CLOCK        0
#define POWER_BUTTON                2
#define POWER_LED                   3

uint16_t state_1 = 0b0101010101010101;
uint16_t state_2 = 0b1010101010101010;
uint32_t timer = 0;
bool change_state = true;
bool power_led_state = true;
bool last_button_state = false;

void setup() {
  DDRB = (1 << SERIAL_INPUT) | (1 << OUTPUT_ENABLE) | (1 << STORAGE_REGISTER_CLOCK) | (1 << SHIFT_REGISTER_CLOCK);
  PORTB = 0;
  DDRD = (1 << POWER_LED);
  PORTD = 0;
  PORTD |= (1 << POWER_BUTTON);
  
}

void loop() {

  if(millis() - timer == 1000){

    if(change_state){

      shift_register_state(state_1);
      change_state = false;

    }
    else {

      shift_register_state(state_2);
      change_state = true;

    }

    timer += 1000;
  }

  bool current_button_state = PIND & (1 << POWER_BUTTON);

  if (current_button_state && !last_button_state) {

    power_led_state = !power_led_state;

    if (power_led_state){

      PORTD |= (1 << POWER_LED);
      state_1 = 0b0101010101010101;
      state_2 = 0b1010101010101010;
    
    }
    else {

      PORTD &= ~(1 << POWER_LED);
      state_1 = 0;
      state_2 = 0;
    
    }
      
  }

  last_button_state = current_button_state;
  
}

void shift_register_state(uint16_t change_state){
  
  PORTB &= ~(1 << STORAGE_REGISTER_CLOCK);
  for (uint8_t i = 0; i < 16; ++i) {

    bool bitValue = ((change_state >> i) & 1);

    if (bitValue){

      PORTB |= (1 << SERIAL_INPUT);
    
    }
    else {

      PORTB &= ~(1 << SERIAL_INPUT);
    
    }

    PORTB |= (1 << SHIFT_REGISTER_CLOCK);
    PORTB &= ~(1 << SHIFT_REGISTER_CLOCK);
  
  }

  PORTB |= (1 << STORAGE_REGISTER_CLOCK);

}
