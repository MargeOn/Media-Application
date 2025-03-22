# PROJECT: MediaPlayer Application

- Project này sẽ thực hiện các chức năng chơi nhạc để mô phỏng hệ thống giải trí trên ô tô
  
![](ImageMediaApp/Drawer_and_kr.png)

### Thông tin về source code:

- Viết bằng ngôn ngữ Qt/QML và C++
- Version Qt 5.14.2 và Qt Creator 4.11.1 
- Build trên Ubuntu 22.04 

### Project bao gồm các kiến thức đã sử dụng như:

- Sử dụng mô hình Model View của Qt 
- Sử dụng ListView, PathView, ListModel
- Cách giao tiếp giữa C++ và QML
- Sử dụng đối tượng QMediaPlayer để thực hiện các chức năng chơi nhạc
- Làm việc với thư viện bên thứ ba: Taglib
- Xây dựng model bằng QAbstractListModel
- Sử dụng đối tượng Drawer của Qt Quick Control để hiển thị danh sách bài hát
- Sử dụng ComboBox của Qt Quick Control để lựa chọn ngôn ngữ
- Hỗ trợ đa ngôn ngữ cho ứng dụng Qt bằng QTranslation

## Cấu trúc chương trình: 
- Chương trình được xây dựng giao diện bằng QML và sử dụng ngôn ngữ C++ để xử lí các thao tác, tính năng cho phần backend
- Phần giao diện được chia thành 3 component chính:
  + AppHeader: bao gồm tên ứng dụng, button đóng - mở playlist và comboBox lựa chọn ngôn ngữ
  + Playlist: hiển thị danh sách bài hát có trong ứng dụng và thao tác chọn bài hát
  + MediaInfo: hiển thị các thông tin bài hát đang được chơi và các thao tác chơi/dừng, lặp lại bài hát, ...
- Phần C++: sử dụng OOP, binding property, kết nối các signal - slot để xử lí các tính năng của ứng dụng
## Chức năng:
- Phát nhạc và dừng nhạc
- Chuyển tiếp bài hát
- Chức năng phát ngẫu nhiên - shuffle
- Chức năng lặp lại bài hát hiện tại - repeat
- Chức năng hiển thị đóng, mở danh sách bài hát
- Chức năng lựa chọn và hiển thị đa ngôn ngữ: Anh, Việt, Hàn, Nhật

### 1. Giao diện ứng dụng:
- Giao diện hiển thị ban đầu sẽ không hiển thị danh sách bài hát:
  
![](ImageMediaApp/background_version2.png)

### 2. Chức năng hiển thị đóng, mở danh sách bài hát:
- Hiển thị danh sách bài hát:

![](ImageMediaApp/Drawer.png)
  
- Lựa chọn bài hát trên danh sách bài hát:

![](ImageMediaApp/luachonbaihat.png)

### 3. Chức năng lựa chọn và hiển thị đa ngôn ngữ: 
- Lựa chọn các ngôn ngữ trong ứng dụng:
    
![](ImageMediaApp/ComboBox_version2.png)

- Lựa chọn tiếng Việt:
  
![](ImageMediaApp/vn.png)

- Lựa chọn tiếng Hàn:
  
![](ImageMediaApp/kr_version2.png)

- Lựa chọn tiếng Nhật:
  
![](ImageMediaApp/jp.png)
