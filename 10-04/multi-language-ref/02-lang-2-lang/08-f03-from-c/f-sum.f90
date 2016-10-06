
! sum up absolute of "num" integers in array "inp"
integer(c_int) function sum_abs(inp, num) bind(C)
  use iso_c_binding, only: c_int
  implicit none
  integer(c_int), intent(in) :: inp(*)
  integer(c_int), intent(in), value :: num
  integer(c_int) :: i,s

   s = 0
   do i=1,num
     s = s + abs(inp(i)); 
   end do
   sum_abs = s;
end function sum_abs
 
