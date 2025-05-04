# Thông tin nhóm

- **Thành viên**:
  - Huỳnh Thái Toàn - MSSV: 23120175 (Nhóm trưởng)
  - Triệu Tuấn Kiệt - MSSV: 23120137
  - Lê Nhật Minh Tâm - MSSV: 23120163

## Phân công công việc

| Thành viên | Phụ trách chính                     | Nhiệm vụ cụ thể                                                                                                                                               | Mức độ hoàn thiện |
|------------|-------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------|
| **Toàn**   | Kiến trúc hệ thống & Business Layer | - Thiết kế kiến trúc tổng thể, phân tích class diagram, luồng nghiệp vụ  <br> - Xây dựng các lớp model: User, Trip, Booking  <br> - Phát triển các service: UserService, TripService, BookingService  <br> - Thiết lập interface repository  <br> - Đề xuất, triển khai các design pattern (Singleton, Factory, Strategy, Repository)  <br> - Review code, hỗ trợ giải quyết vấn đề kỹ thuật |   50% |
| **Tâm**    | Data Access Layer & Database        | - Thiết kế và hiện thực các repository: UserRepository, TripRepository, BookingRepository  <br> - Xây dựng lớp DatabaseConnection, QueryBuilder  <br> - Xử lý đọc/ghi file CSV, mapping DTO  <br> - Đảm bảo các repository tuân thủ interface  <br> - Viết unit test cho các lớp data access  <br> - Hỗ trợ thành viên khác về phần lưu trữ dữ liệu |   30% |
| **Kiệt**   | Presentation Layer & Utils          | - Phát triển UI console: MenuHandler, InputHandler, OutputFormatter  <br> - Xây dựng các view: UserView, TripView, BookingView  <br> - Xây dựng các class tiện ích: Validator, Configuration  <br> - Đảm bảo giao diện người dùng thân thiện, dễ sử dụng  <br> - Định dạng đầu vào/ra, xác thực dữ liệu  <br> - Viết tài liệu hướng dẫn sử dụng, mô tả chức năng UI |   30% |

# Đánh giá mức độ hoàn thành Hệ thống Quản lý Đại lý Du lịch

---

## I. Thiết kế phần mềm và mô hình hướng đối tượng

### 1. Viết lại theo hướng đối tượng

- Các lớp như `User`, `Trip`, `Booking` được xây dựng rõ ràng, mỗi lớp đại diện cho một thực thể trong hệ thống.
- Các lớp dịch vụ `UserService`, `TripService`, `BookingService` xử lý nghiệp vụ tách biệt khỏi giao diện.
- Các repository được xây dựng riêng như `UserRepository`, `TripRepository`, `BookingRepository`.
- Giao diện người dùng đã tách riêng qua các lớp như `MenuHandler`, `InputHandler`, `OutputFormatter`.

### 2. Áp dụng SOLID và Design Patterns

- Tuân thủ SOLID
  - **Single Responsibility Principle(SRP)**: Mỗi lớp chỉ đảm nhiệm một vai trò.
    - `Application`: chỉ chịu trách nhiệm khởi tạo và điều phối các thành phần.
    - `UserService`, `TripService`, `BookingService`: xử lý logic nghiệp vụ tương ứng.
    - `UserRepository`, `TripRepository`, `BookingRepository`: chỉ chịu trách nhiệm truy xuất dữ liệu.
  - **Open/Closed Principle(OCP)**: Có thể mở rộng chức năng dễ dàng qua thêm lớp hoặc hàm mới.
    - Giao diện như `IBookingRepository`, `ITripRepository` cho phép thêm các Repository mới.
  - **Liskov Substitution Principle(LSP)**: Các lớp con (nếu có) sẽ có thể thay thế lớp cha mà không làm hỏng chương trình.
    - Bất kỳ lớp nào kế thừa `ITripRepository`, `IBookingRepository` đều có thể thay thế trong `Application`, `Service`.
  - **Interface Segregation Principle(ISP)**: Các interface được chia nhỏ, không gom nhiều chức năng.
    - Mỗi interface (`IBookingRepository`, `ITripRepository`) **rõ ràng**.
  - **Dependency Inversion Principle(DIP)**: Các dịch vụ phụ thuộc vào interface, không phụ thuộc trực tiếp vào lớp cụ thể.
    - `Application` dùng **interface như `IBookingRepository`**, không trực tiếp gắn với `BookingRepository`.
- Đã áp dụng Singleton Pattern, Repository Pattern để tách lớp dữ liệu khỏi nghiệp vụ.
  - Singleton Pattern
    - `Application` được cài dưới dạng Singleton:

        ```cpp
        static Application& getInstance();
        ```

    - Constructor là `private`, copy constructor và operator= bị xóa.
  - Reponsitory Pattern
    - Các interface như `IBookingRepository`, `ITripRepository` đóng vai trò trung gian giữa Service và dữ liệu.
    - Abstraction giúp truy cập dữ liệu mà không cần biết lưu ở đâu.

### 3. Kiến trúc phần mềm

- Áp dụng mô hình ba lớp (3-layer architecture) như trong mô tả propasal và cấu trúc file đã đề ra

#### Các phần có thể hoàn thiện

- Cơ sở dữ liệu chưa thực sự hoàn chỉnh: mới chỉ dùng file CSV, chưa tích hợp với hệ thống cơ sở dữ liệu như SQLite, MySQL,...

## II. GitHub

### Thống kê đóng góp của các thành viên

Dưới đây là thống kê đóng góp của các thành viên trong dự án, được lấy từ GitHub Insights:

![GitHub Collaboration Insights](https://i.imgur.com/UYewAbU.png)

[Imgur](https://imgur.com/UYewAbU)

---

## Hướng dẫn chạy chương trình

1. **Biên dịch chương trình**:
   - Chạy file `build.bat` trong thư mục `source` của dự án bằng cách nhấp đúp vào nó hoặc mở Command Prompt và thực thi:

     ```
     .\source\build.bat
     ```

   - File batch sẽ tự động biên dịch mã nguồn và tạo file thực thi trong thư mục `release`

2. **Chạy chương trình**:
   - Sau khi biên dịch thành công, vào thư mục `release` và chạy file `TravelAgencySystem.exe`
   - Hoặc từ Command Prompt:

     ```
      .\release\TravelAgencySystem.exe
     ```

3. **Yêu cầu hệ thống**:
   - Windows 10/11
   - Đã cài đặt trình biên dịch C++ (g++ hoặc tương đương)
