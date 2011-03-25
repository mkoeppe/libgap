/****************************************************************************
**
*W  saveload.h                  GAP source                   Steve Linton
**
*H  @(#)$Id: saveload.h,v 4.13 2002/04/15 10:03:57 sal Exp $
**
*Y  Copyright (C)  1997,  Lehrstuhl D fuer Mathematik,  RWTH Aachen,  Germany
*Y  (C) 1998 School Math and Comp. Sci., University of St.  Andrews, Scotland
*Y  Copyright (C) 2002 The GAP Group
**
**  This file declares the functions concerned with saving and loading
**  the workspace. There are support functions in gasman.c and elsewhere
**  throughout the kernel
*/
#ifdef  INCLUDE_DECLARATION_PART
const char * Revision_saveload_h =
   "@(#)$Id: saveload.h,v 4.13 2002/04/15 10:03:57 sal Exp $";
#endif

/***************************************************************************
**

*F  SaveWorkspace( <fname> ) . . . . . .save the workspace to the named file
**
**  'SaveWorkspace' is the entry point to the workspace saving. It is not
**  installed as a GAP function, but instead as a keyword, so that we can be
**  sure it is only being called from the top-most prompt level
**  The file saveload.tex in the dev directory describes the saved format
**  in more detail. Most of the work will be done from inside GASMAN, because
**  we need to fiddle with Bag internals somewhat
**
**  The return value is either True or Fail
*/

extern Obj SaveWorkspace( Obj fname );

extern void LoadWorkspace( Char *fname);

extern void SaveUInt1(UInt1 x);
extern void SaveUInt2(UInt2 x);
extern void SaveUInt4(UInt4 x);
extern void SaveUInt(UInt x);
#ifdef SYS_IS_64_BIT
extern void SaveUInt8(UInt8 x);
#endif
extern void SaveCStr(const Char *s);
extern void SaveString(Obj string);
extern void LoadString(Obj string);
extern void SaveSubObj(Obj o);
extern void SaveHandler(ObjFunc hdlr);

extern UInt1 LoadUInt1( void );
extern UInt2 LoadUInt2( void );
extern UInt4 LoadUInt4( void );
extern UInt LoadUInt( void );
#ifdef SYS_IS_64_BIT
extern UInt8 LoadUInt8( void);
#endif
extern void LoadCStr(Char *buf, UInt maxlen );
extern Obj LoadSubObj( void );
extern ObjFunc LoadHandler();



/***************************************************************************
**

*F * * * * * * * * * * * * * initialize package * * * * * * * * * * * * * * *
*/


/****************************************************************************
**

*F  InitInfoSaveLoad()  . . . . . . . . . . . . . . . table of init functions
*/
StructInitInfo * InitInfoSaveLoad ( void );


/****************************************************************************
**

*E  saveload.h  . . . . . . . . . . . . . . . . . . . . . . . . . . ends here
*/





