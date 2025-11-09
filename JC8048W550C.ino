/*
 * Configurazione Finale dal Datasheet
 *
 * Utilizza i parametri di timing e clock esatti
 * trovati nel file JC8048B050N_I.pdf (Pagina 11, Tabella 4.7)
 * che hai fornito.
 */

#include <Arduino_GFX_Library.h>

#define GFX_BL 2 // Pin della retroilluminazione (HIGH per ON)

// 1. Definizione del BUS (costruttore a 33 argomenti)
Arduino_ESP32RGBPanel *rgb_panel = new Arduino_ESP32RGBPanel(
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */,
    
    // --- TIMING ESATTI DAL PDF (Pag. 11)  ---
    0 /* hsync_polarity */, 8 /* hsync_front_porch */, 8 /* hsync_pulse_width */, 8 /* hsync_back_porch */,
    0 /* vsync_polarity */, 8 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 8 /* vsync_back_porch */,
    // ---------------------------------------------
    
    1 /* pclk_active_neg */, 
    
    // --- CLOCK ESATTO DAL PDF (Pag. 11)  ---
    25000000 /* prefer_speed (25MHz)*/, 
    // -------------------------------------------
    
    true /* auto_flush */,
    
    // Parametri extra (2)
    0 /* de_idle_high */, 0 /* pclk_idle_high */
); // Totale: 33 argomenti

// 2. Definizione del DISPLAY (Classe moderna)
Arduino_GFX *tft = new Arduino_RGB_Display(
    800 /* width */, 480 /* height */, rgb_panel
);


void setup() {
  Serial.begin(115200);
  delay(1000); 
  Serial.println("Test Display V11 - (Core v2 + GFX 33-arg + Timings da PDF)");

  Serial.println("Inizializzazione GFX...");
  if (!tft->begin()) {
    Serial.println("!!! ERRORE: tft->begin() fallito!");
  } else {
    Serial.println("tft->begin() RIUSCITO.");
  }

  // Accendi la retroilluminazione (CORRETTO)
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH); 
  Serial.println("Retroilluminazione impostata su HIGH.");

  // Riempie lo schermo
  Serial.println("Riempimento schermo...");
  tft->fillScreen(BLACK);
  delay(500);
  tft->fillScreen(RED);
  delay(500);
  tft->fillScreen(GREEN);
  delay(500);
  tft->fillScreen(BLUE);
  delay(500);
  tft->fillScreen(BLACK);

  // Disegna elementi di test
  Serial.println("Disegno testo e forme.");
  tft->setCursor(10, 10);
  tft->setTextColor(WHITE);
  tft->setTextSize(3);
  tft->println("FUNZIONA!");
  tft->println("Display 800x480 Test OK!");

  tft->drawRect(50, 100, 100, 50, RED);
  tft->fillRect(200, 100, 100, 50, GREEN);
  tft->drawCircle(450, 125, 50, BLUE);

  Serial.println("Test completato. Entro nel loop.");
}

void loop() {
  tft->drawFastHLine(10, 300, 780, tft->color565(random(255), random(255), random(255)));
  delay(100);
}
