! fourier synthesis code example in fortran 95

MODULE kinds
  IMPLICIT NONE
  SAVE
  INTEGER, PARAMETER :: DP = selected_real_kind(14,200)
END MODULE kinds

SUBROUTINE write_fsynth(freq,phase,intens,fnum,tnum,tmax,fname)
  USE kinds
  IMPLICIT NONE

  CHARACTER(len=*),INTENT(IN) :: fname
  INTEGER, INTENT(IN)         :: fnum,tnum
  REAL(kind=DP),INTENT(IN)    :: freq(1:*),phase(1:*),intens(1:*)
  REAL(kind=DP),INTENT(IN)    :: tmax
  REAL(kind=DP)               :: tdelta,t,val
  REAL(kind=DP),PARAMETER     :: twopi=6.28318530717958647688_DP
  INTEGER :: i,j

  tdelta=tmax/DBLE(tnum)

  OPEN(unit=9,file=TRIM(fname),status='unknown',form='formatted')

  WRITE(9,'(A,I10)') '# ', tnum

  DO i=0,tnum-1
     t=DBLE(i)*tdelta
     val=0.0d0

     DO j=1,fnum
        val=val+intens(j)*SIN(twopi*(freq(j)*t+phase(j)))
     END DO

     WRITE(9,*) t, val
  END DO

  CLOSE(9)

END SUBROUTINE write_fsynth


PROGRAM fsynth
  USE kinds

  IMPLICIT NONE
  INTEGER                   :: fnum,tnum,i
  REAL(kind=DP),ALLOCATABLE :: freq(:),phase(:),intens(:)
  REAL(kind=DP)             :: tmax
  CHARACTER(len=80)         :: fname

  PRINT*,'fourier synthesis'
  PRINT*,'give number of frequencies'
  READ*,fnum
  PRINT*,'got: ',fnum

  ALLOCATE(freq(fnum),phase(fnum),intens(fnum))

  DO i=1,fnum
     PRINT*,'frequency number: ',i
     PRINT*,'give frequency, intensity and phase:'
     READ*,freq(i),intens(i),phase(i)
     PRINT*,'got: ',freq(i),intens(i),phase(i)
  END DO

  PRINT*,'give total time'
  READ*,tmax
  PRINT*,'got: ',tmax
  PRINT*,'give number of intervals'
  READ*,tnum
  PRINT*,'got: ',tnum
  PRINT*,'give filename'
  READ(5,'(A)') fname
  PRINT*,'got: ',TRIM(fname)

  PRINT*,'generating output'
  CALL write_fsynth(freq,phase,intens,fnum,tnum,tmax,TRIM(fname))

!  DEALLOCATE(freq,phase,intens)
      
END PROGRAM fsynth

