
MODULE kinds
  IMPLICIT NONE
  SAVE
  INTEGER, PARAMETER :: DP = selected_real_kind(14,200)
END MODULE kinds

SUBROUTINE printvec(vector,length)
  USE kinds
  IMPLICIT NONE

  REAL(kind=DP), INTENT(IN) :: vector(1:*)
  INTEGER, INTENT(IN)       :: length
  INTEGER                   :: i

  DO i=1,length
     PRINT*, i, vector(i)
  END DO

END SUBROUTINE printvec

PROGRAM arraymem

  USE kinds

  IMPLICIT NONE

  INTEGER       :: i
  REAL(kind=DP) :: avec(4),bvec(4),cvec(4),amat(4,4)

  REAL(kind=DP) :: ddot
  EXTERNAL ddot

  avec(1) = 1.0_DP
  avec(2) = 2.0_DP
  avec(3) = 3.0_DP
  avec(4) = 4.0_DP

  bvec(4) = 1.0_DP
  bvec(3) = 2.0_DP
  bvec(2) = 3.0_DP
  bvec(1) = 4.0_DP

  cvec(1) = 1.0_DP
  cvec(2) = 1.0_DP
  cvec(3) = 1.0_DP
  cvec(4) = 1.0_DP

  DO i=1,4
     amat(i,1) = avec(i)
     amat(i,2) = bvec(i)
     amat(i,3) = cvec(i)
     amat(i,4) = avec(i)
  END DO

  CALL printvec(amat,16)

  PRINT*,'---'

  DO i=1,4
     amat(1,i) = avec(i)
     amat(2,i) = bvec(i)
     amat(3,i) = cvec(i)
     amat(4,i) = avec(i)
  END DO

  CALL printvec(amat,16)

  PRINT*,'---'

  PRINT*, ddot(4,avec,1,bvec,1)

  PRINT*,'---'

  CALL dgemv('T',4,4,1.0_DP,amat,4,bvec,1,0.0_DP,cvec,1)

  CALL printvec(cvec,4)
  
END PROGRAM arraymem
