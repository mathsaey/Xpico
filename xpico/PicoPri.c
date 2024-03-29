/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*              Printing             */
/*-----------------------------------*/

#include <stdio.h>

#include "Pico.h"
#include "PicoMai.h"
#include "PicoMem.h"
#include "PicoEnv.h"
#include "PicoNat.h"
#include "PicoPri.h"
                    
/* private constants */

#define VOI_TEXT "<void>"
#define STO_TEXT "<stop>" //Added Stop text
#define VAR_TEXT "<variable>"
#define APL_TEXT "<application>"
#define TBL_TEXT "<tabulation>"
#define DEF_TEXT "<definition>"
#define SET_TEXT "<assignment>"
#define MSG_TEXT "<message>"
#define DCT_TEXT "<dictionary>"
#define ENV_TEXT "<environment>"
#define NYI_TEXT "<not yet implemented>"

#define EXP _print_EXP_ 

/* private prototypes */

static _NIL_TYPE_ APL(_NIL_TYPE_);
static _NIL_TYPE_ DCT(_NIL_TYPE_);
static _NIL_TYPE_ DEF(_NIL_TYPE_);
static _NIL_TYPE_ FRC(_NIL_TYPE_);
static _NIL_TYPE_ FUN(_NIL_TYPE_);
static _NIL_TYPE_ NAT(_NIL_TYPE_);
static _NIL_TYPE_ NBR(_NIL_TYPE_);
static _NIL_TYPE_ NYI(_NIL_TYPE_);
static _NIL_TYPE_ ENV(_NIL_TYPE_);
static _NIL_TYPE_ SET(_NIL_TYPE_);
static _NIL_TYPE_ TAB(_NIL_TYPE_);
static _NIL_TYPE_ TAb(_NIL_TYPE_);
static _NIL_TYPE_ TBL(_NIL_TYPE_);
static _NIL_TYPE_ TXT(_NIL_TYPE_);
static _NIL_TYPE_ VAR(_NIL_TYPE_);
static _NIL_TYPE_ VOI(_NIL_TYPE_);
static _NIL_TYPE_ STO(_NIL_TYPE_); //Added STO

/* private variables */

static const _CNT_TYPE_ CNT_tab[] = 
   { VOI,
     NAT,
     FRC,
     TXT,
     TAB,
     FUN,
     VAR,
     APL,
     TBL,
     DEF,
     SET,
     DCT,
     ENV,
     STO,//Added stop
     NYI,
     NYI, 
     NBR}; 

/* private functions */

/*------------------------------------------------------------------------*/
/*  APL                                                                   */
/*     expr-stack: [... ... ... ... ... APL] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... APL] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ APL(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(APL_TEXT); }

/*------------------------------------------------------------------------*/
/*  DCT                                                                   */
/*     expr-stack: [... ... ... ... ... DCT] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... DCT] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ DCT(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(DCT_TEXT); }
                               
/*------------------------------------------------------------------------*/
/*  DEF                                                                   */
/*     expr-stack: [... ... ... ... ... DEF] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... DEF] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ DEF(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(DEF_TEXT); }
  
/*------------------------------------------------------------------------*/
/*  FRC                                                                   */
/*     expr-stack: [... ... ... ... ... FRC] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... FRC] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ FRC(_NIL_TYPE_)
 { _EXP_TYPE_ exp;
   _FLP_TYPE_ d;
   _stk_peek_EXP_(exp);
   _stk_poke_EXP_(_EOLN_);
   d = _ag_get_FRC_(exp);
   _stk_zap_CNT_();
   sprintf(_TEXT_BUF_, "%g", *d);
   _print_(_TEXT_BUF_); }
                               
/*------------------------------------------------------------------------*/
/*  FUN                                                                   */
/*     expr-stack: [... ... ... ... ... FUN] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... FUN] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ FUN(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nam;
   _STR_TYPE_ str;
   _stk_peek_EXP_(exp);
   _stk_poke_EXP_(_EOLN_);
   nam = _ag_get_FUN_NAM_(exp);
   _stk_zap_CNT_();
   str = _ag_get_TXT_(nam);
   sprintf(_TEXT_BUF_, "<function %s>", str);
   _print_(_TEXT_BUF_); }
                                
/*------------------------------------------------------------------------*/
/*  NAT                                                                   */
/*     expr-stack: [... ... ... ... ... NAT] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... NAT] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ NAT(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nam;
   _STR_TYPE_ str;
   _stk_peek_EXP_(exp);
   _stk_poke_EXP_(_EOLN_);
   nam = _ag_get_NAT_NAM_(exp);
   _stk_zap_CNT_();
   str = _ag_get_TXT_(nam);
   sprintf(_TEXT_BUF_, "<native function %s>", str);
   _print_(_TEXT_BUF_); }

/*------------------------------------------------------------------------*/
/*  NBR                                                                   */
/*     expr-stack: [... ... ... ... ... NBR] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... NBR] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ NBR(_NIL_TYPE_)
 { _EXP_TYPE_ exp;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(exp);
   _stk_poke_EXP_(_EOLN_);
   nbr = _ag_get_NBR_(exp);
   _stk_zap_CNT_();
   sprintf(_TEXT_BUF_, "%d", nbr);
   _print_(_TEXT_BUF_); }

/*------------------------------------------------------------------------*/
/*  NYI                                                                   */
/*     expr-stack: [... ... ... ... ... NYI] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... NYI] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ NYI(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(NYI_TEXT); }
   
/*------------------------------------------------------------------------*/
/*  SET                                                                   */
/*     expr-stack: [... ... ... ... ... SET] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... SET] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SET(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(SET_TEXT); }
   
/*------------------------------------------------------------------------*/
/*  ENV                                                                   */
/*     expr-stack: [... ... ... ... ... ENV] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... ENV] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ ENV(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(ENV_TEXT); }

/*------------------------------------------------------------------------*/
/*  TBL                                                                   */
/*     expr-stack: [... ... ... ... ... TBL] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... TBL] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TBL(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(TBL_TEXT); }

/*------------------------------------------------------------------------*/
/*  TXT                                                                   */
/*     expr-stack: [... ... ... ... ... TXT] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... TXT] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TXT(_NIL_TYPE_)
 { _EXP_TYPE_ exp;
   _STR_TYPE_ str;
   _stk_peek_EXP_(exp);
   _stk_poke_EXP_(_EOLN_);
   str = _ag_get_TXT_(exp);
   _stk_zap_CNT_();
   _print_(str); }
   
/*------------------------------------------------------------------------*/
/*  TAB                                                                   */
/*     expr-stack: [... ... ... ... ... TAB] -> [... ... ... TAB *1* EXP] */
/*     cont-stack: [... ... ... ... ... TAB] -> [... ... ... ... TAb EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... TAB] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... TAB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TAB(_NIL_TYPE_)
 { _EXP_TYPE_ exp;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(exp);
   siz = _ag_get_TAB_SIZ_(exp);
   if (siz > 0)
     { exp = _ag_get_TAB_EXP_(exp, 1);
       _stk_push_EXP_(_ONE_);
       _stk_push_EXP_(exp);
       _stk_poke_CNT_(TAb);
       _stk_push_CNT_(EXP); 
       _print_("["); }   
   else
     { _stk_poke_EXP_(_EOLN_);
       _stk_zap_CNT_();
       _print_("[]"); }}
                               
/*------------------------------------------------------------------------*/
/*  TAb                                                                   */
/*     expr-stack: [... ... ... TAB NBR VOI] -> [... ... ... TAB NBR EXP] */
/*     cont-stack: [... ... ... ... ... TAb] -> [... ... ... ... TAb EXP] */
/*                                                                              */
/*     expr-stack: [... ... ... ... TAB NBR] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... TAb] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TAb(_NIL_TYPE_)
 { _EXP_TYPE_ nbr, exp, voi;
   _UNS_TYPE_ idx, siz;
   _stk_claim_();
   _stk_pop_EXP_(voi);
   _stk_pop_EXP_(nbr);
   _stk_peek_EXP_(exp);
   idx = _ag_get_NBU_(nbr); 
   siz = _ag_get_TAB_SIZ_(exp);
   if (idx < siz)
     { _stk_push_EXP_(_ag_succ_NBR_(nbr));
       exp = _ag_get_TAB_EXP_(exp, idx+1);
       _stk_push_EXP_(exp); 
       _stk_push_CNT_(EXP);
       _print_(", "); }
   else
     { _stk_poke_EXP_(_EOLN_);
       _stk_zap_CNT_(); 
       _print_("]"); }}

/*------------------------------------------------------------------------*/
/*  VAR                                                                   */
/*     expr-stack: [... ... ... ... ... VAR] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... VAR] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ VAR(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(VAR_TEXT); }

/*------------------------------------------------------------------------*/
/*  VOI                                                                   */
/*     expr-stack: [... ... ... ... ... VOI] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... VOI] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ VOI(_NIL_TYPE_)
 { _stk_poke_EXP_(_EOLN_);
   _stk_zap_CNT_();
   _print_(VOI_TEXT); }

/*------------------------------------------------------------------------*/
/*  STO                                                                   */
/*     expr-stack: [... ... ... ... ... STO] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... STO] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

//Added stop
static _NIL_TYPE_ STO(_NIL_TYPE_)
{ _stk_poke_EXP_(_EOLN_);
  _stk_zap_CNT_();
  _print_(STO_TEXT); }

/* public functions */

/*------------------------------------------------------------------------*/
/*  EXP                                                                   */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... ***] */
/*------------------------------------------------------------------------*/
_NIL_TYPE_ _print_EXP_(_NIL_TYPE_)
 { _EXP_TYPE_ exp;
   _stk_peek_EXP_(exp);
   _stk_poke_CNT_(CNT_tab[_ag_get_TAG_(exp)]); }
