# Projeto controle de servomotor por pwm 

Esse projeto tem como objetivo controlar o servo motor, primeiro o servo motor começa no ângulo de 180°, depois para 90° e depois 0°, e logo em seguida ele se mantem em um loop infinito onde o servo motor rotacion-se entre 0° e 180°.

## Hardware 🛠️

- Microcontrolador RP2040 (Raspberry Pi Pico).
- Servo motor
- LED RGB.
- Placa BitDogLab

## Software 💻

* **SDK do Raspberry Pi Pico:** O SDK (Software Development Kit) do Pico, que inclui as bibliotecas e ferramentas necessárias para desenvolver e compilar o código. [Instruções de instalação](https://www.raspberrypi.com/documentation/pico/getting-started/)
* **CMake:** Um sistema de construção multiplataforma usado para gerar os arquivos de construção do projeto.
* **Compilador C/C++:**  Um compilador C/C++ como o GCC (GNU Compiler Collection).
* **Git:** (Opcional) Para clonar o repositório do projeto.


### O código está dividido em vários arquivos para melhor organização:

- **`PWM_Embarca.c`**: Código que tem como função
- **`CMakeLists.txt`:** Define a estrutura do projeto para o CMake.



## Como Compilar e Executar ⚙️

1. **Instale o SDK do Raspberry Pi Pico:** Siga as instruções no site oficial do Raspberry Pi.
2. **Clone este repositório:** https://github.com/wesiley/ServoMotor_Embarca
3. **Navegue até o diretório do projeto:** `cd ServoMotor_Embarca`
4. **Compile o projeto:** `cmake -B build && cmake --build build`
5. **Copie para o Pico:** Copie o conteúdo da pasta `build` (gerada após a compilação) para o Raspberry Pi Pico. O programa iniciará automaticamente.


## Funcionamento do Loop Principal 🔄 
```
  while (true) {
        set_servo_angle(pulse_width); // Define o ângulo atual
        set_led_brightness(pulse_width); // Ajusta o brilho do LED proporcionalmente
        printf("Pulso: %dµs\n", pulse_width);

        pulse_width += step; // Incrementa ou decrementa o pulso
        if (pulse_width >= 2400 || pulse_width <= 500) {
            step = -step; // Inverte a direção ao atingir os limites
        }

        sleep_ms(10); // Atraso de 10ms para movimentação suave
    }

   
  ```
O loop while (true) garante execução contínua.  O set_serve_angle é para setar o motor nos ângulos 180°, 90° e 0° e o set_led_brightness() altera a intensidade do LED copiando o código utilizado no servomotor para ser mostrado no uso da BitDogLab, if (pulse_width >= 2400 || pulse_width <= 500) é uma condição para quando pulse_width for maior que 2400 e menor que 500, incrementa e decrementa para que ocorra o movimento do motor e a intensidade do led, sleep_ms(10), uma pequena pausa de 10 milissegundos.

## Configuração do pwm.
```
void pwm_setup() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Habilitar o pino GPIO como PWM
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM); // Habilitar o pino GPIO como PWM

    uint slice_servo = pwm_gpio_to_slice_num(SERVO_PIN); // Obter o canal PWM da GPIO do servo
    uint slice_led = pwm_gpio_to_slice_num(LED_PIN); // Obter o canal PWM da GPIO do LED

    pwm_set_clkdiv(slice_servo, PWM_DIVISER); // Definir o divisor de clock do PWM para o servo
    pwm_set_wrap(slice_servo, WRAP_PERIOD); // Definir o valor de wrap (20ms)
    pwm_set_enabled(slice_servo, true); // Habilitar o PWM no slice correspondente ao servo

    pwm_set_clkdiv(slice_led, PWM_DIVISER); // Definir o divisor de clock do PWM para o LED
    pwm_set_wrap(slice_led, WRAP_PERIOD); // Definir o valor de wrap (20ms)
    pwm_set_enabled(slice_led, true); // Habilitar o PWM no slice correspondente ao LED
}
  ```
 gpio_set_function(PWM_motor, GPIO_FUNC_PWM), habilitar o pino GPIO como PWM.   uint slice = pwm_gpio_to_slice_num, obter o canal PWM da GPIO.   pwm_set_clkdiv, define o divisor de clock do PWM.   pwm_set_wrap, definir o valor de wrap.    pwm_set_enabled, habilita o pwm no slice correspondente.

## Reação do LED RGB com o uso do mesmo código do servo motor.

Primeiro o LED RGB na cor azul começa com uma intensidade forte, depois a intensidade diminui pela metade , e depois reduz mais ainda, logo em seguida o Led fica em um loop entre a intensidade mais baixa até a intensidade mais forte, a demosntração acontece no video logo abaixo👇.
 
## Diagrama de Conexões 💡:

https://wokwi.com/projects/422456961770688513

## Próximo Passos ➡️

- fazer o servo motor rotacionar com uma fluidez maior.
  
 ## 🔗 Link do Vídeo de Funcionamento:
 
https://drive.google.com/file/d/1__Vb626H9ck2u7czY7PRV_j202_V6hr6/view?usp=sharing

 ## Contribuições 🤝

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.
