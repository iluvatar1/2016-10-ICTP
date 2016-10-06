C23456789012345678901234567890123456789012345678901234567890123456789012
C        1         2         3         4         5         6         7
C     fourier synthesis code example in fortran 77
      program fsynthx
      implicit none
      integer fnum,fmax,tnum,i
      parameter (fmax=20)
      double precision freq(fmax),phase(fmax),intens(fmax),tmax
      character*80 fname

      print*,'fourier synthesis'
      print*,'give number of frequencies'
      read*,fnum
      print*,'got: ',fnum

      if ((fnum.lt.1).or.(fnum.gt.fmax)) then
        print*,'only 1-',fmax,'fequencies are supported'
        stop 'bad input'
      end if

      do i=1,fnum
        print*,'frequency number: ',i
        print*,'give frequency, intensity and phase:'
        read*,freq(i),intens(i),phase(i)
        print*,'got: ',freq(i),intens(i),phase(i)
      end do

      print*,'give total time'
      read*,tmax
      print*,'got: ',tmax
      print*,'give number of intervals'
      read*,tnum
      print*,'got: ',tnum
      print*,'give filename'
      read(5,'(A)') fname
      print*,'got: ',fname

      print*,'generating output'
      call write_fsynth(fname,freq,phase,intens,fnum,tnum,tmax)

      end

C23456789012345678901234567890123456789012345678901234567890123456789012
C        1         2         3         4         5         6         7
      subroutine write_fsynth(fname,freq,phase,intens,fnum,tnum,tmax)
      implicit none
      integer fnum,tnum
      double precision freq(*),phase(*),intens(*)
      double precision tmax,tdelta,t,val,twopi
      parameter (twopi=6.28318530717958647688)
      integer i,j
      character*(*) fname

      tdelta=tmax/dble(tnum)

      open(unit=9,file=fname,status='unknown',form='formatted')

      write(9,'(A,I10)') '# ', tnum

      do i=0,tnum-1
        t=dble(i)*tdelta
        val=0.0d0

        do j=1,fnum
          val=val+intens(j)*sin(twopi*(freq(j)*t+phase(j)))
        end do

        write(9,*) t, val
      end do

      close(9)

      end
