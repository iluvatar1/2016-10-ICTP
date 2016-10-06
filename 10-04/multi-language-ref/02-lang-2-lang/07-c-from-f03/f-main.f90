program testsum
  use iso_c_binding, only: c_int
  implicit none
  interface
    integer(c_int) function sum_abs(in, num) bind(C)
      use iso_c_binding, only: c_int
      integer(c_int), intent(in) :: in(*)
      integer(c_int), value :: num
    end function sum_abs
  end interface

  integer, parameter :: n=200
  integer :: data(n),i

  do i=1,n
    data(i) = i-100
  end do

  print*, 'sum=',sum_abs(data,n)
end program testsum 
