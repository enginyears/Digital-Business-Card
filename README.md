# 💳 ESP32 Digital Business Card

> A business card that lives inside a $4 microchip. No app, no internet, no paper.

---

## 💡 The Idea

Instead of handing someone a paper card, you hand them an ESP32.  
They connect to its WiFi. Their browser opens your card automatically.  
That's it. Your name, links, and contact info — served from a tiny chip in your pocket.

---

## 🧰 What You Need

| Item | Cost |
|------|------|
| ESP32 Dev Board | ~$4 |
| USB Cable | Already have it |
| VS Code + PlatformIO | Free |
| External components | ❌ None |

---

## 🚀 How to Run It

1. Clone this repo or copy `main.cpp`
2. Open in VS Code with PlatformIO
3. **Edit the card details** in the top section of main.cpp
4. Click Upload (→)
5. Connect your phone to WiFi: `My Digital Card` / password: `helloworld`
6. Open browser → `http://192.168.4.1`

---

## ✏️ Customise Your Card

Find this section at the top of `main.cpp` and fill in your own details:

```cpp
const char* CARD_NAME  = "Your Name Here";
const char* CARD_TITLE = "Your Title";
const char* CARD_EMAIL = "you@email.com";
const char* CARD_PHONE   = "+911234567890";
const char* CARD_INSTA = "@yourhandle";
```

---

## 🧠 What You Learn

- Setting up ESP32 as a WiFi Access Point
- Running a basic web server on the ESP32
- Serving HTML pages from a microcontroller
- String building in C++

---

## 📺 Part of the `enginyears` Beginner Series
> *One ESP32. Infinite possibilities. Starting from zero.*

Instagram: [@enginyears](https://instagram.com/enginyears.me)
