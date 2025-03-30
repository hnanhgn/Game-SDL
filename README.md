# 🌼 Bee Garden Adventure 🐝

## 🎮 Giới thiệu
**Bee Garden Adventure** là một trò chơi thú vị, nơi người chơi điều khiển nhân vật để trồng hoa, thu hoạch và tránh những con ong đang tìm kiếm mật.

## 🕹️ Lối chơi
- Người chơi sẽ **gieo hạt giống**, chăm sóc hoa và **thu hoạch** khi hoa nở.
- Cần **hái đủ số hoa trong thời gian quy định** để vượt qua từng level.
- Cẩn thận với **những con ong**! Chúng sẽ bay quanh vườn để tìm hoa và có thể làm nhân vật bị choáng nếu va chạm.
- Game có **4 level với độ khó tăng dần**, người chơi phải vượt qua tất cả để chiến thắng.

## 🔧 Logic game
- **Gieo hạt giống**: Mỗi hoa cần 2 hạt, nhưng các hoa tiếp theo cần 3 hạt.
- **Thu hoạch hoa**: Hái nhanh trước khi ong đến lấy mật.
- **Ong hút mật**: Nếu người chơi không hái kịp, ong sẽ lấy hoa.
- **Ong tấn công**: Nếu chạm vào ong, nhân vật bị choáng và mất mạng.
- **Thua cuộc** nếu hết thời gian hoặc hết mạng.

## 🎨 Đồ họa & Âm thanh
### **🔹 Đồ họa:**
- Màn hình **Chào mừng**, **Chọn level**, **Chơi game**.
- Nhân vật bay liên tục, có hiệu ứng **choáng** khi bị ong đốt.
- Mô phỏng **quá trình phát triển hoa** từ hạt giống → nụ → nở hoa.

### **🔹 Âm thanh:**
- Nhạc nền chạy xuyên suốt game.
- Âm thanh khi click chuột.
- Âm thanh **khóc khi bị ong đốt**, **vui khi thắng level**.

## 📁 Cấu trúc project
```
├── src/
│   ├── beeOperation.cpp // Điều khiển hành động của ong
│   ├── characterMovement.cpp // Xử lý di chuyển nhân vật
│   ├── button.cpp // Xử lý sự kiện nút bấm
│   ├── definition.h // Định nghĩa hằng số
│   ├── flowerGrowth.cpp // Xử lý hoa nở
│   ├── textureManager.cpp // Quản lý hình ảnh
│   ├── updateScore.cpp // Cập nhật điểm số
│   ├── main.cpp // Vòng lặp game
└── assets/
    ├── images/ // Hình ảnh, background
    ├── sounds/ // Nhạc nền, hiệu ứng âm thanh
```

## 🚀 Cài đặt & Chạy game
### **1️⃣ Cài đặt SDL2** (nếu chưa có)
```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```

### **2️⃣ Clone project từ GitHub**
```bash
git clone https://github.com/yourusername/bee-garden-game.git
cd bee-garden-game
```

### **3️⃣ Biên dịch & chạy game**
```bash
g++ -o game src/*.cpp -lSDL2 -lSDL2_image -lSDL2_mixer
./game
```

## 📜 Điều khiển nhân vật
- **Mũi tên trái/phải/lên/xuống**: Di chuyển nhân vật.
- **Phím Space**: Gieo hạt giống.
- **Phím Enter**: Thu hoạch hoa.
- **Chuột**: Nhấn vào các nút trong menu.
- **ESC**: Dừng trò chơi.

## 🎯 Mục tiêu game
- Hoàn thành **4 level**, hái đủ số hoa trước khi hết thời gian!
- Tránh ong để không mất mạng!
- Nếu hoàn thành tất cả, bạn **chiến thắng**!

---
🎮 **Chúc bạn chơi vui vẻ!** 🌼🐝
