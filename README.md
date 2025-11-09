# Test Display 5" e Touch per ESP32-S3 (JC8048W550C)

Questo repository contiene un codice di esempio fondamentale per l'inizializzazione e il test del display LCD RGB da 5 pollici (800x480) e del touchscreen capacitivo (GT911) per il modulo **JC8048W550C** (noto anche come `ESP32-8048S050`).

Questo modulo è basato su un **ESP32-S3** con PSRAM Octal (OPI) e richiede una configurazione molto specifica dell'IDE Arduino per funzionare, che è stata determinata dopo un lungo debug.

##  Hardware di Riferimento
* **Modulo:** `JC8048W550C`
* **Chip:** `ESP32-S3`
* **Display:** 800x480 RGB Parallelo (Driver `ST7262`)
* **Touch:** Capacitivo (Driver `GT911` via I2C)

---

## 🔧 La Configurazione "Coppia d'Oro"
Per compilare e caricare con successo il codice, l'ambiente dell'IDE Arduino **deve** essere configurato con questa esatta combinazione di versioni, che risolve i conflitti noti tra il Core ESP32 v3.x e la PSRAM OPI.

### 1. Gestore Schede (Boards Manager)
* **Pacchetto:** `esp32` di Espressif Systems
* **Versione:** `v2.0.17` (o la v2.x.x più recente)
    > **IMPORTANTE:** Il Core **v3.x.x** causa un crash all'avvio (`Dcache error` / `Cache error`) su questo hardware e **non deve** essere usato.

### 2. Gestore Librerie (Libraries)
* **Libreria Display:** `GFX Library for Arduino` (di Moon On Our Nation)
    * **Versione:** `v1.4.x` (o qualsiasi versione che richieda **33 argomenti** per il costruttore `Arduino_ESP32RGBPanel`).
* **Libreria Touch:** `TAMC_GT911` (di TAMC)
    * **Versione:** (La più recente va bene)

### 3. Impostazioni del Menu "Strumenti" dell'IDE
Questa è la configurazione esatta richiesta:

* **Board:** "ESP32S3 Dev Module"
* **USB CDC On Boot:**
    * `Enabled` (Per il test *solo display*, per vedere `Serial.print`)
    * `**Disabled**` (**Obbligatorio** per il test *del touch*)
* **Flash Mode:** "QIO 80MHz"
* **Flash Size:** "16MB (128Mb)"
* **Partition Scheme:** "16M Flash (..." (Qualsiasi opzione da 16MB)
* **PSRAM:** "**OPI PSRAM**"

---

## ⚠️ "Gotchas" Fondamentali (Perché questa config?)
1.  **Core V3 vs V2:** L'uso del Core ESP32 v3.x causa un crash hardware (`Dcache preload parameter configuration error`) all'avvio quando si inizializza la `OPI PSRAM`. La soluzione è usare il **Core v2.x.x**.
2.  **GFX Library vs Core:** La libreria `Arduino_GFX` v2.x *richiede* il Core v3.x (causando un errore di compilazione `esp32-hal-periman.h`). La soluzione è usare la "Coppia d'Oro": **Core v2.x.x** + **Libreria GFX v1.4.x** (che usa il costruttore a 33 argomenti).
3.  **Touch vs Seriale:** Il touch `GT911` usa I2C sui pin **GPIO 19 (SDA)** e **GPIO 20 (SCL)**. L'ESP32-S3 usa questi stessi pin per il `USB CDC` (il Monitor Seriale). Per usare il touch, **`USB CDC On Boot` deve essere impostato su `Disabled`**.

---
