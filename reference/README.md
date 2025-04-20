# Đề xuất Cải tiến Hệ thống Quản lý Đại lý Du lịch

## Giới thiệu

Đề xuất này trình bày kế hoạch để cải tiến Hệ thống Quản lý Đại lý Du lịch hiện tại từ mã nguồn theo phong cách thủ tục sang một hệ thống hướng đối tượng, dễ bảo trì và mở rộng. Hệ thống hiện tại cung cấp các chức năng cơ bản để quản lý chuyến du lịch, người dùng và kế hoạch chuyến đi.

Link project: <https://www.codewithc.com/travel-agency-management-system-in-c-with-mysql/>

## Viết lại theo hướng đối tượng

Mã nguồn thủ tục sẽ được viết lại hoàn toàn theo nguyên tắc hướng đối tượng, với các lớp chính sau (dự kiến):

```
- Application (điểm vào chính)
- Models
  - User (Người dùng)
  - Trip (Chuyến đi)
  - Booking (Đặt chỗ)
- Services
  - UserService (Dịch vụ người dùng)
  - TripService (Dịch vụ chuyến đi)
  - BookingService (Dịch vụ đặt chỗ)
- Repositories
  - UserRepository
  - TripRepository
  - BookingRepository
- Database
  - Phần này có thể giả lập lưu CSDL vào file csv 
     và lấy CSDL từ file đó chứ không sử dụng DBMS
- UI
  - MenuHandler (Xử lý menu)
  - InputHandler (Xử lý đầu vào)
  - OutputFormatter (Định dạng đầu ra)
- Utils
  - Validator (Xác thực)
  - Configuration (Cấu hình)
```

Mỗi lớp sẽ có trách nhiệm rõ ràng và phân tách rõ ràng giữa dữ liệu, logic nghiệp vụ và thành phần giao diện người dùng.

## Áp dụng SOLID và Design Patterns

Hệ thống sau khi cải tiến sẽ tuân thủ các nguyên tắc SOLID:

1. **Single Responsibility Principle (Nguyên tắc đơn trách nhiệm)**

2. **Open/Closed Principle (Nguyên tắc đóng mở)**

3. **Liskov Substitution Principle (Nguyên tắc thay thế Liskov)**
  
4. **Interface Segregation Principle (Nguyên tắc phân tách giao diện)**
  
5. **Dependency Inversion Principle (Nguyên tắc đảo ngược phụ thuộc)**
  
Hệ thống sẽ triển khai các mẫu thiết kế sau:

1. **Singleton Pattern**
2. **Factory Pattern**
3. **Strategy Pattern**
4. **Repository Pattern**
5. **...**

## Kiến trúc phần mềm

**Sử dụng kiến trúc three-layer**

Cấu trúc file dự kiến:

```
src/
├── presentation/  (Presentation Layer)
│   ├── menu/
│   │   ├── MainMenu.h/cpp
│   │   ├── UserMenu.h/cpp
│   │   ├── TripMenu.h/cpp
│   │   └── BookingMenu.h/cpp
│   ├── view/
│   │   ├── UserView.h/cpp
│   │   ├── TripView.h/cpp
│   │   └── BookingView.h/cpp
│   └── console/
│       ├── InputHandler.h/cpp
│       └── OutputFormatter.h/cpp
│
├── business/  (Business Layer)
│   ├── services/
│   │   ├── UserService.h/cpp
│   │   ├── TripService.h/cpp
│   │   └── BookingService.h/cpp
│   ├── models/
│   │   ├── User.h/cpp
│   │   ├── Trip.h/cpp
│   │   └── Booking.h/cpp
│   └── interfaces/
│       ├── IUserRepository.h
│       ├── ITripRepository.h
│       └── IBookingRepository.h
│
└── data/  (Data Access Layer)
    ├── repositories/
    │   ├── UserRepository.h/cpp
    │   ├── TripRepository.h/cpp
    │   └── BookingRepository.h/cpp
    ├── database/
    │   ├── DatabaseConnection.h
    │   └── QueryBuilder.h/cpp
    └── dto/
        ├── UserDTO.h/cpp
        ├── TripDTO.h/cpp
        └── BookingDTO.h/cpp
```

## Đảm bảo chất lượng mã nguồn

### Quy trình Git

Triển khai Quy trình Feature Branch (Feature Branch Workflow):

1. **Main Branch**: Mã nguồn ổn định cho sản phẩm
2. **Develop Branch**: Branch tích hợp cho các tính năng
3. **Feature Branches**: Các tính năng riêng lẻ phát triển độc lập
   - Định dạng: `feature/ten-tinh-nang`
4. **Hotfix Branches**: Cho các sửa lỗi khẩn cấp
   - Định dạng: `hotfix/mo-ta-loi`

### Coding Convention

Các quy ước mã hóa sau sẽ được áp dụng:

#### Quy ước đặt tên

- **Classes**: PascalCase (ví dụ: `TripService`)
- **Methods**: camelCase (ví dụ: `findUserById`)
- **Variables**: camelCase (ví dụ: `userName`)
- **Constants**: UPPER_SNAKE_CASE (ví dụ: `MAX_USERS`)
- **Private Members**: Tiền tố với dấu gạch dưới (ví dụ: `_connection`)

#### Tổ chức file

- Một lớp trên mỗi file
- Tên file theo tên lớp chứa trong đó
- Nhóm các file liên quan trong các thư mục thích hợp

## Unit Testing Chi tiết

### 1. Unit Tests cho Quản lý Đặt chỗ (BookingService)

#### Happy Path

- **Test tạo đặt chỗ mới thành công**
- **Test tìm đặt chỗ theo ID**
- **Test cập nhật trạng thái đặt chỗ**

#### Edge Cases

- **Test đặt chỗ với số lượng người tối đa**
- **Test đặt chỗ vào ngày cuối của chuyến đi**
- **Test đặt chỗ đúng vào thời điểm hết hạn**

#### Error Handling

- **Test đặt chỗ với người dùng không tồn tại**
- **Test đặt chỗ với chuyến đi không tồn tại**
- **Test đặt chỗ với số lượng người âm hoặc bằng 0**
- **Test đặt chỗ khi chuyến đi đã đầy**

### 2. Unit Tests cho Quản lý Người dùng (UserService)

#### Happy Path

- **Test đăng ký người dùng mới**
- **Test đăng nhập**
- **Test cập nhật thông tin người dùng**

#### Edge Cases

- **Test đăng ký với email đúng định dạng nhưng phức tạp**
- **Test đăng ký với mật khẩu đúng độ dài tối thiểu**
- **Test thay đổi mật khẩu đến độ dài tối đa**:

#### Error Handling

- **Test đăng ký với email đã tồn tại**
- **Test đăng nhập với email không tồn tại**
- **Test đăng nhập với mật khẩu sai**
- **Test cập nhật người dùng không tồn tại**

### 3. Unit Tests cho Quản lý Chuyến đi (TripService)

#### Happy Path

- **Test tạo chuyến đi mới**
- **Test tìm chuyến đi theo ID**
- **Test tìm kiếm chuyến đi theo tiêu chí**
- **Test cập nhật thông tin chuyến đi**

#### Edge Cases

- **Test tạo chuyến đi có thời gian bắt đầu = thời gian kết thúc**
- **Test cập nhật giảm số chỗ của chuyến đi xuống đúng bằng số đã đặt**
- **Test tìm kiếm chuyến đi với kết quả rỗng nhưng hợp lệ**

#### Error Handling

- **Test tạo chuyến đi với ngày bắt đầu muộn hơn ngày kết thúc**
- **Test tạo chuyến đi với giá âm**
- **Test tạo chuyến đi với số chỗ không hợp lệ**
- **Test cập nhật chuyến đi không tồn tại**
- **Test cập nhật giảm số chỗ thấp hơn số đặt chỗ hiện tại**

.v.v.
