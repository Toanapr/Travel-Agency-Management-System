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
# Travel Agency Management System - Hệ thống Quản lý Đại lý Du lịch

## Thành viên nhóm
- **Huỳnh Thái Toàn** - MSSV: 23120175 (Nhóm trưởng)
- **Triệu Tuấn Kiệt** - MSSV: 23120137
- **Lê Nhật Minh Tâm** - MSSV: 23120163

## Liệt kê các công việc mà từng thành viên đã thực hiện

### Huỳnh Thái Toàn (Nhóm trưởng)
- Thiết kế kiến trúc tổng thể của hệ thống theo mô hình 3 tầng
- Phân tích và thiết kế class diagram, luồng nghiệp vụ
- Xây dựng các lớp model: User, Trip, Booking
- Phát triển các service: UserService, TripService, BookingService
- Thiết lập các interface repository (IUserRepository, ITripRepository, IBookingRepository)
- Xây dựng lớp Application chính để quản lý toàn bộ hệ thống
- Review code và hỗ trợ giải quyết các vấn đề kỹ thuật
- Viết unit test

### Lê Nhật Minh Tâm
- Thiết kế và hiện thực các repository: UserRepository, TripRepository, BookingRepository
- Xây dựng lớp DatabaseConnection để quản lý kết nối dữ liệu
- Phát triển các DTO và mapper cho việc chuyển đổi dữ liệu
- Xử lý đọc/ghi file CSV, quản lý persistence
- Đảm bảo các repository tuân thủ interface đã định nghĩa
- Xử lý các tình huống lỗi trong việc truy cập dữ liệu
- Viết documentation

### Triệu Tuấn Kiệt
- Phát triển UI console: MenuHandler, InputHandler, OutputFormatter
- Xây dựng các view: UserView, TripView, BookingView
- Xây dựng các class tiện ích: Validator, Configuration
- Thiết kế menu và giao diện người dùng
- Xử lý validation đầu vào và format đầu ra
- Tạo các script build và deployment (build.bat)
- Viết tài liệu hướng dẫn sử dụng cho end-user
- Test UI/UX và cải thiện trải nghiệm người dùng

## Tỉ lệ đóng góp của các thành viên vào dự án

| Thành viên | Tỉ lệ đóng góp | Công việc chính |
|------------|----------------|-----------------|
| Huỳnh Thái Toàn | 35% | Kiến trúc hệ thống, Business Layer, Test Unit |
| Lê Nhật Minh Tâm | 32% | Data Access Layer, File I/O, Document |
| Triệu Tuấn Kiệt | 33% | Presentation Layer, UI/UX, Test Manual |
| **Tổng** | **100%** | |

## Tỉ lệ điểm của các thành viên (chia đều)

| Thành viên | Tỉ lệ điểm |
|------------|------------|
| Huỳnh Thái Toàn | 33.33% |
| Lê Nhật Minh Tâm | 33.33% |
| Triệu Tuấn Kiệt | 33.33% |
| **Tổng** | **100%** |

## Video demo
[Video Demo - Travel Agency Management System](https://youtu.be/jP3l2pom2dk)
[https://youtu.be/jP3l2pom2dk]

---

# Các mô tả cụ thể

## Teamwork

### Phân công và theo dõi tiến độ công việc
Nhóm đã phân chia công việc một cách rõ ràng dựa trên kiến trúc 3 tầng:
- **Toàn**: Chịu trách nhiệm thiết kế tổng thể và tầng Business Logic
- **Tâm**: Phụ trách tầng Data Access và quản lý dữ liệu  
- **Kiệt**: Đảm nhiệm tầng Presentation và giao diện người dùng

Tiến độ được theo dõi qua:
- Sử dụng GitHub để quản lý source code và track changes
- Trao đổi qua nhóm chat để giải quyết vấn đề

### Hình ảnh GitHub Commit
[Hình ảnh GitHub commit history sẽ được cập nhật sau]

## Cải tiến mã nguồn mẫu

### Cài đặt lại chức năng của mã nguồn mẫu theo hướng đối tượng

So với mã nguồn gốc được viết theo phong cách thủ tục với các hàm toàn cục, chúng em đã tái cấu trúc hoàn toàn theo hướng đối tượng:

**Mã nguồn gốc:**
- Sử dụng biến toàn cục (global variables)
- Không có phân tách trách nhiệm
- Khó bảo trì và mở rộng

**Mã nguồn sau khi cải tiến:**
- Tổ chức thành các lớp rõ ràng theo từng chức năng
- Áp dụng kiến trúc 3 tầng (Presentation, Business, Data)
- Sử dụng interface và dependency injection
- Phân tách rõ ràng giữa UI, business logic và data access
- Dễ dàng test và maintain

### Các chức năng thêm và cải tiến

1. **Quản lý người dùng:**
   - Thêm validation đầy đủ cho thông tin người dùng
   - Hỗ trợ tìm kiếm theo nhiều tiêu chí (ID, tên)
   - Chinh sửa và xóa người dùng
   - Thêm nguời dùng mới với thông tin đầy đủ

2. **Quản lý chuyến đi chi tiết hơn:**
   - Quản lý địa điểm khởi hành
   - Theo dõi số lượng chỗ ngồi còn trống
   - Tim kiếm chuyến đi theo nhiều tiêu chí (ID, Tên)
   - Thêm chuyến đi mới với thông tin đầy đủ
   - Hỗ trợ chỉnh sửa và xóa chuyến đi

3. **Quản lý đặt chỗ:**
   - Tự động tính toán giá dựa trên số người và loại chuyến đi
   - Quản lý trạng thái booking (Pending, Confirmed, Cancelled)
   - Kiểm tra tự động số chỗ còn trống
   - Hỗ trợ hủy và chỉnh sửa booking
   - Tim kiếm booking theo nhiều tiêu chí (ID, User ID, Trip ID)
### Giao diện bố trí 

- **Menu hierarchical**: Tổ chức menu theo nhóm chức năng logic
- **Input validation**: Kiểm tra và hướng dẫn người dùng nhập liệu đúng format
- **Output formatting**: Hiển thị dữ liệu dưới dạng bảng đẹp mắt, dễ đọc
- **Error handling**: Thông báo lỗi rõ ràng với hướng dẫn khắc phục
- **Navigation**: Dễ dàng quay lại menu chính hoặc thoát chương trình
- **Confirmation dialogs**: Xác nhận trước khi thực hiện các thao tác quan trọng

## Kiến trúc phần mềm + Design Pattern

### Kiến trúc phần mềm

Chúng em đã thiết kế hệ thống theo **kiến trúc 3 tầng (3-layer Architecture)**:

1. **Presentation Layer (Tầng giao diện)**:
   - `MenuHandler`: Quản lý điều hướng menu
   - `InputHandler`: Xử lý đầu vào từ người dùng
   - `OutputFormatter`: Format và hiển thị dữ liệu
   - Các View classes: `UserView`, `TripView`, `BookingView`

2. **Business Layer (Tầng nghiệp vụ)**:
   - Models: `User`, `Trip`, `Booking` - Đại diện cho các thực thể nghiệp vụ
   - Services: `UserService`, `TripService`, `BookingService` - Xử lý logic nghiệp vụ
   - Interfaces: Định nghĩa contract giữa các tầng

3. **Data Access Layer (Tầng dữ liệu)**:
   - Repositories: `UserRepository`, `TripRepository`, `BookingRepository`
   - `DatabaseConnection`: Quản lý kết nối và file operations
   - DTOs: Data Transfer Objects cho việc mapping

### Tuân thủ các nguyên tắc và nguyên lý OOP

**SOLID Principles:**

1. **Single Responsibility Principle (SRP)**:
   - Mỗi class chỉ có một lý do để thay đổi
   - VD: `UserService` chỉ xử lý logic nghiệp vụ liên quan đến User

2. **Open/Closed Principle (OCP)**:
   - Sử dụng interfaces để mở rộng chức năng mà không sửa đổi code cũ
   - VD: `IUserRepository` có thể implement nhiều cách lưu trữ khác nhau

3. **Liskov Substitution Principle (LSP)**:
   - Các derived class có thể thay thế base class mà không ảnh hưởng chương trình
   - VD: Bất kỳ implementation nào của `IUserRepository` đều hoạt động đúng

4. **Interface Segregation Principle (ISP)**:
   - Chia nhỏ interfaces thành các phần chuyên biệt
   - VD: `IUserRepository`, `ITripRepository` tách biệt rõ ràng

5. **Dependency Inversion Principle (DIP)**:
   - High-level modules không phụ thuộc vào low-level modules
   - Services phụ thuộc vào interfaces, không phụ thuộc concrete classes

**OOP Principles:**
- **Encapsulation**: Dữ liệu được che dấu trong private members, chỉ truy cập qua public methods
- **Inheritance**: Sử dụng kế thừa hợp lý cho các base classes
- **Polymorphism**: Sử dụng virtual functions và interfaces
- **Abstraction**: Tạo abstract interfaces cho repositories và services

### Design Patterns đã áp dụng

1. **Singleton Pattern**:
   - Áp dụng cho class `Application`
   - Đảm bảo chỉ có một instance duy nhất của ứng dụng
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
2. **Repository Pattern**:
   - Tách biệt business logic khỏi data access logic
   - Cung cấp interface thống nhất cho việc truy cập dữ liệu
   - Dễ dàng thay đổi cơ chế lưu trữ (CSV, Database, API)

3. **Factory Pattern**:
   - `RepositoryFactory` để tạo các repository instances
   - Giúp quản lý việc khởi tạo objects phức tạp

4. **Model-View-Controller (MVC)**:
   - Mô hình này được áp dụng trong Presentation Layer
   - `View` classes hiển thị dữ liệu, `Controller` xử lý logic và `Model` chứa dữ liệu
## Đảm bảo chất lượng

### Testing

Hệ thống được kiểm thử toàn diện với cả kiểm thử tự động và kiểm thử thủ công. Chi tiết đầy đủ về kế hoạch kiểm thử có thể tham khảo tại [TEST_PLAN.md](source/test/TEST_PLAN.md).

**Kiểm thử tự động với Google Test:**

1. **Kiểm thử đơn vị (Unit Tests)**:
   - **Kiểm thử Model**: Kiểm tra constructor, getters/setters, validation cho User, Trip, Booking
   - **Kiểm thử Repository**: Kiểm tra các thao tác CRUD, chức năng tìm kiếm, xử lý lỗi
   - **Kiểm thử Service**: Kiểm tra logic nghiệp vụ, tích hợp với repositories

2. **Tổ chức kiểm thử**:
   ```
   source/test/
   ├── model_tests/        # Kiểm thử cho business models
   ├── repository_tests/   # Kiểm thử cho data repositories  
   ├── service_tests/      # Kiểm thử cho business services
   ├── CMakeLists.txt      # Cấu hình CMake
   ├── build_tests.bat     # Script build
   └── TEST_PLAN.md        # Chi tiết kế hoạch kiểm thử
   ```

3. **Hướng dẫn nhanh**:
   ```bash
   # Build và chạy tests
   cd source/test
   ./build_tests.bat      # Windows
   ./build_tests.sh       # Linux/Mac
   ```

4. **Build và kiểm thử tự động**:
   - Script `build_tests.bat` để build và chạy tests
   - Tích hợp CMake để quản lý dependencies
   - Google Test framework tự động download và setup
   - Xem chi tiết tại [README.md](source/test/README.md)

**Kiểm thử thủ công:**
- Kiểm thử UI/UX cho điều hướng menu
- Kiểm thử tích hợp cho quy trình end-to-end
- Kiểm thử hiệu năng với datasets lớn
- Kiểm thử chấp nhận người dùng


### Quy ước lập trình

1. **Quy ước đặt tên**:
   - Classes: PascalCase (`UserService`, `BookingRepository`)
   - Methods: camelCase (`getUserById`, `createBooking`)
   - Private members: tiền tố underscore (`_userId`, `_name`)
   - Constants: UPPER_SNAKE_CASE (`MAX_USERS`, `DEFAULT_CAPACITY`)

### Coding Convention

1. **Naming Convention**:
   - Classes: PascalCase (`UserService`, `BookingRepository`)
   - Methods: camelCase (`getUserById`, `createBooking`)
   - Private members: underscore prefix (`_userId`, `_name`)
   - Constants: UPPER_SNAKE_CASE (`MAX_USERS`, `DEFAULT_CAPACITY`)

2. **Code Organization**:
   - Header files (.h) chứa declarations
   - Implementation files (.cpp) chứa definitions
   - Mỗi class một file riêng biệt
   - Folder structure theo layers

3. **Documentation**:
   - Doxygen comments cho tất cả public methods
   - Inline comments cho logic phức tạp

4. **Error Handling**:
   - Sử dụng exceptions

## Tài liệu mô tả kiến trúc phần mềm và các module

### Doxygen Documentation

Hệ thống được tài liệu hóa đầy đủ bằng Doxygen, bao gồm:

**Cấu trúc tài liệu:**
- **HTML Documentation**: Tài liệu web đầy đủ với navigation và search
- **Class Documentation**: Mô tả chi tiết các classes, methods và attributes
- **File Documentation**: Tài liệu cho từng source file
- **Dependency Graphs**: Biểu đồ phụ thuộc giữa các modules

**Truy cập tài liệu:**
```bash
# Mở tài liệu HTML
cd source/docs/html
python3 -m http.server 8000
# Then open http://localhost:8000 in your browserl       # Linux
```

**Các tài liệu chính:**
- [`Application`](source/docs/html/_application_8h.html) - Class quản lý chính của hệ thống
- [`User`](source/docs/html/_user_8h.html), [`Trip`](source/docs/html/_trip_8h.html), [`Booking`](source/docs/html/_booking_8h.html) - Business models
- Repository classes - Data access layer
- Service classes - Business logic layer
- View classes - Presentation layer

**Tạo lại tài liệu:**
```bash
# Yêu cầu Doxygen được cài đặt
doxygen Doxyfile
```

Tài liệu Doxygen cung cấp:
- Class hierarchy và inheritance diagrams
- Method signatures với parameters và return types
- Code examples và usage notes
- Cross-references giữa các components
- Include dependency graphs

Xem thêm tại thư mục [`source/docs/`](source/docs/) để truy cập đầy đủ documentation

## Class Diagram Mermaid
Travel Agency System - Class Diagram (lượt bỏ các chi tiết không cần thiết để giữ cho sơ đồ ngắn gọn)

```mermaid
classDiagram
    class User {
        -int id
        -string name
        -string address
        -string phone
        -string email
        +User()
        +getId() int
        +getName() string
        +setName(string) void
    }
    class Trip {
        -int id
        -string name
        -double cost
        -int availableSeats
        -string startDate
        -string endDate
        +Trip()
        +getId() int
        +getName() string
        +getCost() double
    }
    class Booking {
        -int id
        -int userId
        -int tripId
        -string bookingDate
        -int numberOfPeople
        -double totalCost
        -string status
        +Booking()
        +getId() int
        +getUserId() int
        +getTripId() int
    }
    class IUserRepository {
        <<interface>>
        +getAll() vector
        +getById(int) User
        +add(User) bool
        +update(User) bool
        +remove(int) bool
    }
    class ITripRepository {
        <<interface>>
        +getAll() vector
        +getById(int) Trip
        +add(Trip) bool
        +update(Trip) bool
        +remove(int) bool
    }
    class IBookingRepository {
        <<interface>>
        +getAll() vector
        +getById(int) Booking
        +add(Booking) bool
        +update(Booking) bool
        +remove(int) bool
    }
    class UserRepository {
        -DatabaseConnection dbConnection
        +UserRepository()
        +getAll() vector
        +getById(int) User
        +add(User) bool
        +update(User) bool
        +remove(int) bool
    }
    class TripRepository {
        -DatabaseConnection dbConnection
        +TripRepository()
        +getAll() vector
        +getById(int) Trip
        +add(Trip) bool
        +update(Trip) bool
        +remove(int) bool
    }
    class BookingRepository {
        -DatabaseConnection dbConnection
        +BookingRepository()
        +getAll() vector
        +getById(int) Booking
        +add(Booking) bool
        +update(Booking) bool
        +remove(int) bool
    }
    class UserService {
        -IUserRepository userRepository
        +UserService()
        +getAllUsers() vector
        +addUser(User) bool
        +updateUser(User) bool
        +deleteUser(int) bool
    }
    class TripService {
        -ITripRepository tripRepository
        +TripService()
        +getAllTrips() vector
        +addTrip(Trip) bool
        +updateTrip(Trip) bool
        +deleteTrip(int) bool
    }
    class BookingService {
        -IBookingRepository bookingRepository
        +BookingService()
        +getAllBookings() vector
        +createBooking(Booking) bool
        +updateBooking(Booking) bool
        +cancelBooking(int) bool
    }
    class DatabaseConnection {
        -string dataPath
        +DatabaseConnection()
        +connect(string) bool
        +disconnect() void
        +isConnected() bool
    }
    class Application {
        -UserService userService
        -TripService tripService
        -BookingService bookingService
        +Application()
        +initialize() void
        +run() void
    }
    class MenuHandler {
        -UserService userService
        -TripService tripService
        -BookingService bookingService
        +MenuHandler()
        +start() void
    }
    class InputHandler {
        +getInt() int
        +getString() string
        +getChoice(int, int) int
        +validateEmail(string) bool
    }
    class OutputFormatter {
        +printHeader(string) void
        +printSuccess(string) void
        +printError(string) void
        +printUser(User) void
        +printTrip(Trip) void
        +printBooking(Booking) void
    }
    UserRepository ..|> IUserRepository
    TripRepository ..|> ITripRepository
    BookingRepository ..|> IBookingRepository
    UserService --> IUserRepository
    TripService --> ITripRepository
    BookingService --> IBookingRepository
    UserRepository --> DatabaseConnection
    TripRepository --> DatabaseConnection
    BookingRepository --> DatabaseConnection
    Application --> UserService
    Application --> TripService
    Application --> BookingService
    Application --> MenuHandler
    User "1" -- "0..*" Booking
    Trip "1" -- "0..*" Booking
