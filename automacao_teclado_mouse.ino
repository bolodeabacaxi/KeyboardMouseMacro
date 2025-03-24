#include <Keyboard.h>
#include <Mouse.h>

const int switchPin = 13; // Pino do switch
const int numPresses = 100; // Número de vezes que cada tecla (1, 2, 3) será pressionada
const int tecla1 = '1'; 
const int tecla2 = '2'; 
const int tecla3 = '3'; 
const int teclaSetaDireita = KEY_RIGHT_ARROW; // Define a seta direita do teclado

const long minKeyInterval = 4000; // Tempo mínimo entre pressionamentos de tecla (4s - 6s)
const long maxKeyInterval = 6000;
const long minClickInterval = 1000; // Tempo mínimo entre cliques do botão direito (1s - 3s)
const long maxClickInterval = 3000;
const long setaPressTime = 120000; // 2 minutos pressionando seta direita (120s)
const long setaPauseTime = 50000; // 50 segundos de pausa
const long delayMouseTime = 20000; // 20 segundos antes de começar a mexer o mouse

unsigned long lastKeyPress = 0; 
unsigned long lastMouseClick = 0; 
unsigned long lastSetaStart = 0; 
unsigned long lastSetaEnd = 0;
long nextKeyInterval = 0; 
long nextClickInterval = 0;
int keyStage = 0;
int keyPressCount = 0;
bool pressionandoSeta = false;
bool moveuMouse = false;
bool rodando = false;

void setup() {
  pinMode(switchPin, INPUT_PULLUP); // Configura pino do switch como entrada com pull-up interno
  Keyboard.begin();
  Mouse.begin();
  delay(1000);
}

void loop() {
  if (!rodando) {
    if (digitalRead(switchPin) == LOW) { // Espera o botão ser pressionado
      delay(50); // Pequeno debounce
      rodando = true;

      // Inicializa os tempos após o botão ser pressionado
      nextKeyInterval = random(minKeyInterval, maxKeyInterval);
      nextClickInterval = random(minClickInterval, maxClickInterval);
      lastSetaStart = millis();
      pressionandoSeta = true;
    }
    return; // Não executa o código até o botão ser pressionado
  }

  unsigned long currentMillis = millis();

  // Pressiona teclas '1', '2' e '3' em ordem
  if (keyPressCount < numPresses * 3 && currentMillis - lastKeyPress >= nextKeyInterval) {
    pressKey();
    lastKeyPress = currentMillis;
    nextKeyInterval = random(minKeyInterval, maxKeyInterval);
  }

  // Clique do botão direito do mouse a cada 1 a 3 segundos
  if (currentMillis - lastMouseClick >= nextClickInterval) {
    Mouse.click(MOUSE_RIGHT);
    lastMouseClick = currentMillis;
    nextClickInterval = random(minClickInterval, maxClickInterval);
  }

  // Controle da seta direita (2 min pressionando, 50s parado)
  if (pressionandoSeta) {
    if (currentMillis - lastSetaStart >= setaPressTime) {
      Keyboard.release(teclaSetaDireita);
      pressionandoSeta = false;
      lastSetaEnd = currentMillis;
      moveuMouse = false; // Permite que o movimento do mouse aconteça
    } else {
      Keyboard.press(teclaSetaDireita);
    }
  } else {
    // Aguarda 20 segundos antes de mexer o mouse
    if (!moveuMouse && currentMillis - lastSetaEnd >= delayMouseTime) {
      Mouse.move(6000, 0); // Move o mouse para a direita 500 pixels
      delay(700);
      Mouse.press(MOUSE_LEFT);
      delay(120);
      Mouse.release(MOUSE_LEFT);

      delay(700);
      Mouse.move(-6000, 0); // Move o mouse para a esquerda 500 pixels
      delay(700);
      Mouse.press(MOUSE_LEFT);
      delay(120);
      Mouse.release(MOUSE_LEFT);
      delay(700);

      Mouse.move(-6000, 0); // Move o mouse para a esquerda mais 500 pixels
      delay(700);
      Mouse.press(MOUSE_LEFT);
      delay(120);
      Mouse.release(MOUSE_LEFT);

      delay(500);
      Mouse.move(6000, 0); // Move o mouse para a direita 600 pixels
      

      moveuMouse = true; // Marca que já moveu o mouse e clicou para evitar repetições
    }

    // Após 50s, volta a pressionar a seta direita
    if (currentMillis - lastSetaEnd >= setaPauseTime) {
      lastSetaStart = currentMillis;
      pressionandoSeta = true;
    }
  }
}

// Função para pressionar as teclas '1', '2' e '3' em ordem
void pressKey() {
  char key;
  
  if (keyStage == 0) key = tecla1;
  else if (keyStage == 1) key = tecla2;
  else key = tecla3;

  Keyboard.press(key);
  delay(100);
  Keyboard.release(key);

  keyPressCount++;

  if (keyPressCount % numPresses == 0) {
    keyStage++;
  }
}
