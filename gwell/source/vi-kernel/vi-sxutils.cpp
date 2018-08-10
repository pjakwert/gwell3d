#ifdef __GNUG__
#pragma implementation
#endif


#include "sxinterp.hh"
#include "matrixh3f.hh"

namespace Vi {

 void InitMtxFrom( SxInterp &Interp, MatrixH3f &Mtx ) throw (Sx::Exception)
 {
   SXCMD_DEFINE_VAR;
   MatrixH3f::AnglesType AType;
   AngleUnit             AUnit;
   Vector3f  Ang,Trans,Scale;

   SXCMD_START_LOOP2END(Interp,("Angles",'A')("Translation",'T')("Scale",'S'))
     case 'A': 
              SXCMD_START_LOOP(Interp,("Euler",'E')("XYZ",'X'));
		case 'E': AType = MatrixH3f::AT_Euler;  SXCMD_BREAK_THIS_LOOP;
                case 'X': AType = MatrixH3f::AT_xyz;    SXCMD_BREAK_THIS_LOOP;
              SXCMD_END_LOOP(Interp);
              SXCMD_START_LOOP(Interp,("Deg",'D')("Rad",'r'));
		case 'D': AUnit = AU_Deg;  SXCMD_BREAK_THIS_LOOP;    
                case 'R': AUnit = AU_Rad;  SXCMD_BREAK_THIS_LOOP;
              SXCMD_END_LOOP(Interp);
              Interp.GetVector(Ang.x,Ang.y,Ang.z);
              continue;
    case 'T':
              Interp.LookForChar(':');
              Interp.GetVector(Trans.x,Trans.y,Trans.z);
              continue;
    case 'S':
              Interp.LookForChar(':');
              Interp.GetVector(Scale.x,Scale.y,Scale.z);
              continue;
  SXCMD_END_LOOP(Interp)
  if (AUnit == AU_Deg)  convert_deg2rad(Ang);
  switch (AType) {
   case MatrixH3f::AT_Euler:
      Mtx.SetMatrix_Euler_TAfterR_Rad(Ang,Trans,Scale);
      break;
   case MatrixH3f::AT_xyz:
      Mtx.SetMatrix_XYZ_TAfterR_Rad(Ang,Trans,Scale);
      break;
  }
 }

}
