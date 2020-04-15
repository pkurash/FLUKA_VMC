*======================================================================*
      SUBROUTINE FLUKA_OPENOUT(IOUNIT,FILNAM)
*
*----------------------------------------------------------------------*
* Opens a file with a given unit number
*
*
* IOUNIT: Input unit to be assiged to the file
* FILNAM: Name of the file
*
*----------------------------------------------------------------------*
*

      IMPLICIT NONE
      INTEGER IOUNIT
      CHARACTER*(*) FILNAM

      OPEN (UNIT=IOUNIT, FILE=FILNAM, STATUS="UNKNOWN")

      RETURN
 9999 END


*
*=== FLUKA_CLOSEINP ====================================================*
*
      SUBROUTINE FLUKA_CLOSEINP(IOUNIT)
*
*----------------------------------------------------------------------*
* Closes the given unit number
*
*
* IOUNIT: Input unit to be assiged to the file
*
*----------------------------------------------------------------------*
*
      IMPLICIT NONE
      INTEGER IOUNIT


      CLOSE (UNIT=IOUNIT)

      RETURN
 9999 END
