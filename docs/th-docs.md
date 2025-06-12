# ESP32S3 + LED P5 OUTDOOR SMD1921 MATRIX PANEL

โปรเจกต์นี้สำหรับควบคุมจอ **LED HUB75 P5 OUTDOOR SMD1921** ด้วยบอร์ด **ESP32-S3**

พร้อมตัวอย่างฟังก์ชันการแสดงผลหลายรูปแบบ

## โครงสร้างโปรเจกต์

```bash
├── boards/
│ └── esp32-s3-devkitc-n16r8v1.1.json
├── docs/
│ ├── image1.png
│ └── image2.png
├── include/
│ └── README
├── lib/
│ ├── Adafruit BusIO
│ ├── Adafruit GFX Library
│ └── ESP32 HUB75 LED MATRIX PANEL DMA Display
│ └── README
├── src/
│ └── main.cpp
├── test/
│ └── README
├── .gitignore
├── platformio.ini
└── README.md
```

---

## ข้อมูลฮาร์ดแวร์

- **MCU**: ESP32-S3
- **LED PANEL**: P5 OUTDOOR SMD1921, HUB75, 64x32px ต่อ panel
- **จำนวน panel ที่ต่อร่วม**: 2 columns x 3 rows (รวม 6 panel)
- **ไฟเลี้ยง**: 5V (ควรใช้ >=4A ขึ้นไป)

## แสดงผลของโปรเจกต์
```
		       Size (128x96)
		    +-------+-------+
      IN →  | 1 → △ | 2 ↓ △ |
   		    +-------+-------+
			| 4 ↓ ▽ | 3 ← ▽ |
			+-------+-------+
			| 5 → △ | 6 ↓ △ |
			+-------+-------+
```

### กำหนดขา (Pinout) ที่ใช้

| Signal | ESP32-S3 GPIO |
| --- | --- |
| R1 | 36 |
| G1 | 38 |
| B1 | 40 |
| R2 | 35 |
| G2 | 16 |
| B2 | 4 |
| A | 2 |
| B | 18 |
| C | 42 |
| D | 21 |
| LAT | 1 |
| OE | 9 |
| CLK | 8 |
| E | -1 |

---

## วิธีการใช้งาน

### 1. ติดตั้ง Library ที่จำเป็น

- [ESP32-HUB75-MatrixPanel-I2S-DMA](https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-I2S-DMA)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO)

### 2. อัพโหลดโค้ดผ่าน [PlatformIO](https://platformio.org/)

- เปิดโฟลเดอร์นี้ใน VSCode + PlatformIO
- อัพโหลดไฟล์ `src/main.cpp` ขึ้นบอร์ด

### 3. ตัวอย่างเอาต์พุตที่แสดงผล

- ทดสอบสีพื้น, ข้อความ, เลื่อนข้อความ, กราฟิก ฯลฯ
- มีการแสดง panel mapping, ความละเอียดของจอ, กรอบ, X, ฯลฯ

---

## ฟีเจอร์ที่มีในตัวอย่างนี้

- แสดงข้อความ, ตัวเลข, สี, กราฟิก
- เลื่อนข้อความแบบ marquee
- วาดเส้น กรอบ และ pattern
- Mapping หลาย panel ต่อรวม
- โหมดทดสอบความละเอียดจอ และแสดงชื่อ panel แยกแต่ละแผง

---

## ตัวอย่าง output
<p align="center">
  <img src="docs/image1.png" alt="Preview 1" width="320"/>
  <img src="docs/image2.png" alt="Preview 2" width="320"/>
</p>
---

## เครดิตและข้อมูลเพิ่มเติม

- Repo: [ESP32-HUB75-MatrixPanel-I2S-DMA](https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-I2S-DMA)
- เขียนโดย: [LEKPCSTEAM](https://github.com/lekpcsteam)
- License: MIT

---

## หมายเหตุ

- ถ้าแสดงผลเพี้ยน ลองสลับ chain type หรือ setRotation หรือเช็คสายไฟ
- ถ้ามีปัญหาไฟไม่พอ Panel กระพริบ ให้เพิ่มกำลังจ่ายไฟ

---