/* Arduino USB HID Keyboard - WSAD Pins */
/* SE CONECTAN LOS PINES A GND; NO CONECTAR A 5V*/

uint8_t buf[8] = { 0 }; 

// Definimos los pines para cada tecla
const int pinW = 1;
const int pinS = 2;
const int pinA = 3;
const int pinD = 4;

// Códigos HID para W, S, A, D
// W = 26, S = 22, A = 4, D = 7
const int hidW = 26;
const int hidS = 22;
const int hidA = 4;
const int hidD = 7;

void setup() {
  Serial.begin(9600);

  // Configuramos pines como entrada con resistencia pull-up interna
  pinMode(pinW, INPUT_PULLUP);
  pinMode(pinS, INPUT_PULLUP);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinD, INPUT_PULLUP);
  
  delay(200);
}

void loop() {
  bool pressed = false;

  // Revisamos cada pin. Si está en LOW, es que se pulsó el botón.
  if (digitalRead(pinW) == LOW) { buf[2] = hidW; pressed = true; }
  else if (digitalRead(pinS) == LOW) { buf[2] = hidS; pressed = true; }
  else if (digitalRead(pinA) == LOW) { buf[2] = hidA; pressed = true; }
  else if (digitalRead(pinD) == LOW) { buf[2] = hidD; pressed = true; }

  if (pressed) {
    Serial.write(buf, 8); // Envía la tecla presionada
  } else {
    releaseKey();         // Si no hay nada presionado, suelta las teclas
  }

  delay(50); // Pequeño debounce para evitar rebotes eléctricos
}

void releaseKey() {
  buf[2] = 0;
  Serial.write(buf, 8); 
}