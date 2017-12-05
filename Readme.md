# Readme for Midterm Examine

### ---------------- INFO ----------------
1. ID: 1512029
2. Name: Trần Quốc Bảo
3. Emal: tranquocbao3897@gmail.com
4. Version Visual Studio: Community 2017.
5. Release: Bản release được build ở dạng release.

### -------------- FEATURES --------------
1. Quản lý chi tiêu.
2. Quản lý thu nhập.
3. Thống kê được chi tiêu, thu nhập và summary (xem tiết kiệm được ban nhiêu)
Chức năng Summary nằm trong Menu bar.
4. Người dùng có thể sử dụng phím tab để nhập thông tin nhanh, ít sử dụng chuột.
5. Lưu danh sách chi tiêu và thu nhập. Không tự động lưu mà hỏi người dùng
có muốn lưu trước khi thoát hay không. Có chức năng cho người dùng mở tập tin.
6. Lưu file dưới dạng CSV UTF-8 (Comma delimited). Để người dùng có thể chỉnh sửa bằng excel.
7. Biểu đồ thống kê sử dụng biểu đồ tròn (GDI+), hiển thị đầy đủ các thông tin
như là tổng cộng và phần trăm của từng loại, và tổng chi tiêu hoặc thu nhập.
8. Biểu đồ luôn được cập nhật lúc người dùng thay đổi dữ liệu.
9. Danh sách chi tiêu, thu nhập sử dụng ListView, nên có một số chức năng nâng cao:
- Sắp xếp dữ liệu của một cột khi người dùng bấm vào cột,
có hiển thị dấu mũi tên để biết khi nào là tăng khi nào là giảm.
- Khi nhấp chuột phải vào một item trong danh sách,
hiện ra context menu cho phép người dùng chọn xóa item hoặc chỉnh sửa item.
- Khi người dùng chọn chỉnh sửa item thì hiện ra một dialog để người dùng chỉnh sửa thông tin item đó.
- Trước khi sửa hoặc xóa item đều hỏi sự xác nhận của người dùng.

### ---------- CATCH EXCEPTION -----------
1. Bắt được lỗi tập tin không đúng định dạng.
2. Bắt lỗi không có đủ thông tin để thêm item.
3. bắt lỗi giá tiền (value) không đúng định dạng số thực.

### ------------- ATTENTION --------------
1. Chương trình được build Bản VS Community 2017 ver 15.4.4
(Có thể phải retarget về phiên bản thấp hơn)
2. File csv export từ chương trình có thể mở bằng excel,
nhưng lưu ý khi chỉnh sửa bằng excel phải lưu file dưới dạng CSV UTF-8 (Comma delimited)
như vậy chương trình mới có thể đọc được.

### ------------ LINK BITBUCKET -----------
> https://1512029@bitbucket.org/1512029/hook.git
```
Chú ý link repository trên là private đã add key public của giáo viên.
Đồng thời add user tdquang_edu vào repository với quyền read.
```
### ------------- LINK YOUTUBE ------------
> https://youtu.be/8E89wzvjM5o