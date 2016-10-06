! fourier analysis

MODULE kinds
  IMPLICIT NONE
  SAVE
  INTEGER, PARAMETER :: DP = selected_real_kind(14,200)
END MODULE kinds

PROGRAM fanalyze
  USE kinds
  IMPLICIT NONE
  INCLUDE 'fftw3.f'
  COMPLEX(kind=DP), ALLOCATABLE :: signal(:), freq(:)
  REAL(kind=DP)   :: delta, norm, fnorm, a, b, c
  REAL(kind=DP), PARAMETER :: M_PI=3.14159265358979323844
  INTEGER(kind=8) :: plan
  INTEGER         :: fnum, i

  PRINT*,'# fourier analysis'
  READ(5,'(2X,I8)') fnum
  PRINT*,'# data set has',fnum,' elements'

  ALLOCATE(signal(fnum),freq(fnum))

  DO i=1,fnum
      READ(5,*) a,b
      delta = a - c
      c = a
      signal(i) = CMPLX(b,0.0,DP)
  END DO

  PRINT*,'# total time', delta*fnum
  fnorm = 1.0_DP / (delta * fnum)
  norm = 2.0_DP / fnum

  CALL dfftw_plan_dft_1d(plan,fnum,signal,freq,FFTW_FORWARD,FFTW_ESTIMATE)
  CALL dfftw_execute_dft(plan, signal, freq)

  PRINT*,'# frequency intensity  phase'

  DO i=1,fnum/2
      a = norm * SQRT(REAL(freq(i))**2 + AIMAG(freq(i))**2)
      b = 0.5_DP * (ATAN2(AIMAG(freq(i)),REAL(freq(i)))/M_PI + 0.5_DP)
      IF (b < 0.0_DP) b = b + 1.0_DP
      IF (a > 0.001_DP) WRITE(6,'(3F8.4)') (i-1)*fnorm,a,b
  END DO

  CALL dfftw_destroy_plan(plan)
  DEALLOCATE(signal,freq)

END PROGRAM fanalyze
