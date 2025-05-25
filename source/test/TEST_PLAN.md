# Travel Agency Management System - Test Plan

## 1. Tổng quan hệ thống
Hệ thống quản lý đại lý du lịch được xây dựng với kiến trúc phân tầng:
- **Presentation Layer**: Console UI, Menu handlers
- **Business Layer**: Services (UserService, TripService, BookingService) và Models (User, Trip, Booking)
- **Data Layer**: Repositories, Database connection (CSV files)

## 2. Phạm vi kiểm thử

### 2.1 Automated Tests (Google Test)
Hệ thống sử dụng Google Test framework để thực hiện kiểm thử tự động cho các thành phần sau:

#### 2.1.1 Model Classes
- **User Model**
  - Constructor validation
  - Getter/Setter methods
  - ID validation

- **Trip Model**  
  - Constructor validation
  - Getter/Setter methods
  - Cost and available seats validation
  - Date format validation

- **Booking Model**
  - Constructor validation
  - Getter/Setter methods
  - Status validation

#### 2.1.2 Repository Classes
- **UserRepository**
  - CRUD operations (Create, Read, Update, Delete)
  - Search functionality
  - Error handling
  - File I/O operations

- **TripRepository**
  - CRUD operations
  - Search functionality
  - Error handling
  - File I/O operations

- **BookingRepository**
  - CRUD operations
  - Search by user/trip
  - Error handling
  - File I/O operations

#### 2.1.3 Service Classes  
- **UserService**
  - User management operations
  - Integration with repositories
  - Error handling

- **TripService**
  - Trip management operations
  - Availability checking
  - Integration with repositories

- **BookingService**
  - Booking creation logic
  - Cost calculation
  - Seat availability validation
  - Status management
  - Booking cancellation

### 2.2 Manual Tests
Một số chức năng của hệ thống được kiểm thử thủ công do phụ thuộc vào tương tác người dùng hoặc giao diện console:

- **UI/UX Testing**
  - Menu navigation
  - Input validation
  - Display formatting
  - Error message display

- **Integration Testing**
  - End-to-end workflow testing
  - Data consistency across operations
  - Performance with large datasets

- **User Acceptance Testing**
  - Usability testing
  - Business requirements validation
  - Edge case scenarios

## 3. Test Cases Chi tiết

### 3.1 User Model Tests
- **ConstructorValidData**: Kiểm tra khởi tạo User với dữ liệu hợp lệ
- **ConstructorInvalidData**: Kiểm tra khởi tạo User với dữ liệu không hợp lệ
- **Getters**: Kiểm tra các phương thức getter
- **Setters**: Kiểm tra các phương thức setter
- **IdValidation**: Kiểm tra validation cho ID

### 3.2 Trip Model Tests
- **ConstructorValidData**: Kiểm tra khởi tạo Trip với dữ liệu hợp lệ
- **ConstructorInvalidData**: Kiểm tra khởi tạo Trip với dữ liệu không hợp lệ
- **Getters**: Kiểm tra các phương thức getter
- **Setters**: Kiểm tra các phương thức setter
- **CostValidation**: Kiểm tra validation cho cost
- **AvailableSeatsValidation**: Kiểm tra validation cho available seats
- **DateValidation**: Kiểm tra validation cho date format

### 3.3 Booking Model Tests
- **ConstructorValidData**: Kiểm tra khởi tạo Booking với dữ liệu hợp lệ
- **ConstructorInvalidData**: Kiểm tra khởi tạo Booking với dữ liệu không hợp lệ
- **Getters**: Kiểm tra các phương thức getter
- **Setters**: Kiểm tra các phương thức setter
- **StatusValidation**: Kiểm tra validation cho status

### 3.4 UserRepository Tests
- **AddUser**: Kiểm tra thêm người dùng mới
- **GetById**: Kiểm tra lấy người dùng theo ID
- **GetAll**: Kiểm tra lấy tất cả người dùng
- **Update**: Kiểm tra cập nhật thông tin người dùng
- **Delete**: Kiểm tra xóa người dùng
- **FindByName**: Kiểm tra tìm kiếm người dùng theo tên
- **ErrorHandling**: Kiểm tra xử lý lỗi

### 3.5 TripRepository Tests
- **AddTrip**: Kiểm tra thêm chuyến đi mới
- **GetById**: Kiểm tra lấy chuyến đi theo ID
- **GetAll**: Kiểm tra lấy tất cả chuyến đi
- **Update**: Kiểm tra cập nhật thông tin chuyến đi
- **Delete**: Kiểm tra xóa chuyến đi
- **FindByName**: Kiểm tra tìm kiếm chuyến đi theo tên
- **ErrorHandling**: Kiểm tra xử lý lỗi

### 3.6 BookingRepository Tests
- **AddBooking**: Kiểm tra thêm đặt chỗ mới
- **GetById**: Kiểm tra lấy đặt chỗ theo ID
- **GetAll**: Kiểm tra lấy tất cả đặt chỗ
- **Update**: Kiểm tra cập nhật thông tin đặt chỗ
- **Delete**: Kiểm tra xóa đặt chỗ
- **FindByUserId**: Kiểm tra tìm kiếm đặt chỗ theo user ID
- **FindByTripId**: Kiểm tra tìm kiếm đặt chỗ theo trip ID
- **ErrorHandling**: Kiểm tra xử lý lỗi

### 3.7 UserService Tests
- **GetAllUsers**: Kiểm tra lấy tất cả người dùng
- **GetUserById**: Kiểm tra lấy người dùng theo ID
- **CreateUser**: Kiểm tra tạo người dùng mới
- **UpdateUser**: Kiểm tra cập nhật thông tin người dùng
- **DeleteUser**: Kiểm tra xóa người dùng
- **FindUsersByName**: Kiểm tra tìm kiếm người dùng theo tên

### 3.8 TripService Tests
- **GetAllTrips**: Kiểm tra lấy tất cả chuyến đi
- **GetTripById**: Kiểm tra lấy chuyến đi theo ID
- **CreateTrip**: Kiểm tra tạo chuyến đi mới
- **UpdateTrip**: Kiểm tra cập nhật thông tin chuyến đi
- **DeleteTrip**: Kiểm tra xóa chuyến đi
- **FindTripsByName**: Kiểm tra tìm kiếm chuyến đi theo tên
- **SearchTripsByCriteria**: Kiểm tra tìm kiếm chuyến đi theo tiêu chí

### 3.9 BookingService Tests
- **GetAllBookings**: Kiểm tra lấy tất cả đặt chỗ
- **GetBookingById**: Kiểm tra lấy đặt chỗ theo ID
- **FindBookingsByUserId**: Kiểm tra tìm kiếm đặt chỗ theo user ID
- **FindBookingsByTripId**: Kiểm tra tìm kiếm đặt chỗ theo trip ID
- **CreateBookingValidData**: Kiểm tra tạo đặt chỗ với dữ liệu hợp lệ
- **CreateBookingInvalidUser**: Kiểm tra tạo đặt chỗ với người dùng không hợp lệ
- **CreateBookingInvalidTrip**: Kiểm tra tạo đặt chỗ với chuyến đi không hợp lệ
- **CreateBookingInsufficientSeats**: Kiểm tra tạo đặt chỗ khi không đủ chỗ ngồi
- **UpdateBookingStatus**: Kiểm tra cập nhật trạng thái đặt chỗ
- **CancelBooking**: Kiểm tra hủy đặt chỗ
- **CalculateTotalCost**: Kiểm tra tính tổng chi phí
- **ValidateBooking**: Kiểm tra validation cho đặt chỗ

## 4. Hướng dẫn build và chạy tests

### 4.1 Yêu cầu
- CMake (phiên bản 3.14 trở lên)
- Trình biên dịch C++ hỗ trợ C++17 (GCC, MinGW, MSVC)
- Kết nối internet (để tải Google Test lần đầu)

### 4.2 Cách build tests
1. Mở terminal/command prompt
2. Di chuyển đến thư mục `source/test`
3. Chạy script build:
   - Windows: `build_tests.bat`
   - Linux/Mac: `./build_tests.sh`

Hoặc thực hiện các bước thủ công:
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"  # Hoặc sử dụng generator khác tùy vào hệ thống
mingw32-make                   # Hoặc 'make' trên Linux/Mac
```

### 4.3 Chạy tests
Sau khi build thành công, chạy file thực thi tests:
- Windows: `.\build\travel_agency_tests.exe`
- Linux/Mac: `./build/travel_agency_tests`

### 4.4 Các chức năng cần test thủ công
Các chức năng sau đây cần được kiểm thử thủ công do phụ thuộc vào tương tác người dùng:

1. **Menu Navigation**: Kiểm tra việc điều hướng qua các menu
2. **Input Validation**: Kiểm tra xử lý đầu vào không hợp lệ
3. **Error Handling**: Kiểm tra hiển thị thông báo lỗi
4. **Booking Workflow**: Kiểm tra quy trình đặt chỗ từ đầu đến cuối
5. **User Management**: Kiểm tra quy trình quản lý người dùng
6. **Trip Management**: Kiểm tra quy trình quản lý chuyến đi
7. **File I/O**: Kiểm tra lưu trữ và đọc dữ liệu từ file CSV

## 5. Tổng kết
Kế hoạch kiểm thử này kết hợp cả kiểm thử tự động (sử dụng Google Test) và kiểm thử thủ công để đảm bảo chất lượng của hệ thống quản lý đại lý du lịch. Kiểm thử tự động tập trung vào các thành phần core của hệ thống (models, repositories, services), trong khi kiểm thử thủ công tập trung vào trải nghiệm người dùng và các quy trình nghiệp vụ.