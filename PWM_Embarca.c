#include <stdio.h> // Biblioteca padrão da linguagem C
#include "pico/stdlib.h" // Subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" // Biblioteca para controlar o hardware de PWM

#define SERVO_PIN 22 // Pino GPIO conectado ao servomotor
const uint16_t WRAP_PERIOD = 20000; // Valor máximo do contador - WRAP (20ms para 50Hz)
const float PWM_DIVISER = 50.0; // Divisor do clock para o PWM (ajustado para 50Hz)

// Função para configurar o módulo PWM
void pwm_setup() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, PWM_DIVISER); // Definir o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD); // Definir o valor de wrap (20ms)
    pwm_set_enabled(slice, true); // Habilitar o PWM no slice correspondente
}

// Função para definir o ângulo do servomotor
void set_servo_angle(uint16_t pulse_width_us) {
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint16_t level = (pulse_width_us * WRAP_PERIOD) / 8000; // Converter microssegundos para nível PWM
    pwm_set_gpio_level(SERVO_PIN, level); // Definir o ciclo ativo (duty cycle)
}

// Função principal
int main() {
    stdio_init_all(); // Inicializa o sistema padrão de I/O

    pwm_setup(); // Configura o PWM

    // Posiciona o servomotor em 180° (2.400µs)
    set_servo_angle(2400);
    printf("Posição: 180°\n");
    sleep_ms(5000); // Aguarda 5 segundos

    // Posiciona o servomotor em 90° (1.470µs)
    set_servo_angle(1470);
    printf("Posição: 90°\n");
    sleep_ms(5000); // Aguarda 5 segundos

    // Posiciona o servomotor em 0° (500µs)
    set_servo_angle(500);
    printf("Posição: 0°\n");
    sleep_ms(5000); // Aguarda 5 segundos

    // Rotina para movimentação suave entre 0° e 180°
    uint16_t pulse_width = 500; // Começa em 0° (500µs)
    int8_t step = 5; // Incremento/decremento de 5µs --> 20000 us/ 5us = 4000 --> WRAP / 4000 -> 50000/4000 -> 12.5
    while (true) {
        set_servo_angle(pulse_width); // Define o ângulo atual
        printf("Pulso: %dµs\n", pulse_width);

        pulse_width += step; // Incrementa ou decrementa o pulso
        if (pulse_width >= 2400 || pulse_width <= 500) {
            step = -step; // Inverte a direção ao atingir os limites
        }

        sleep_ms(10); // Atraso de 10ms para movimentação suave
    }

    return 0;
}