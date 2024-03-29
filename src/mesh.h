#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Mesh {

/* This first implementation allows for runnable code */
/* and is not meant to be optimal. Final implementation */
/* should separate declaration and allocation phases */
/* so that allocation can be scheduled in a cache conscious */
/* manner. */

public:

   /**************/
   /* Allocation */
   /**************/

   inline void AllocateNodalPersistent(size_t size)
   {
      m_x.resize(size) ;
      m_y.resize(size) ;
      m_z.resize(size) ;

      m_xd.resize(size, Real_t(0.)) ;
      m_yd.resize(size, Real_t(0.)) ;
      m_zd.resize(size, Real_t(0.)) ;

      m_xdd.resize(size, Real_t(0.)) ;
      m_ydd.resize(size, Real_t(0.)) ;
      m_zdd.resize(size, Real_t(0.)) ;

      m_fx.resize(size) ;
      m_fy.resize(size) ;
      m_fz.resize(size) ;

      m_nodalMass.resize(size, Real_t(0.)) ;
   }

   inline void AllocateElemPersistent(size_t size)
   {
      m_matElemlist.resize(size) ;
      m_nodelist.resize(8*size) ;

      m_lxim.resize(size) ;
      m_lxip.resize(size) ;
      m_letam.resize(size) ;
      m_letap.resize(size) ;
      m_lzetam.resize(size) ;
      m_lzetap.resize(size) ;

      m_elemBC.resize(size) ;

      m_e.resize(size, Real_t(0.)) ;

      m_p.resize(size, Real_t(0.)) ;
      m_q.resize(size) ;
      m_ql.resize(size) ;
      m_qq.resize(size) ;

      m_v.resize(size, 1.0) ;
      m_volo.resize(size) ;
      m_delv.resize(size) ;
      m_vdov.resize(size) ;

      m_arealg.resize(size) ;
   
      m_ss.resize(size) ;

      m_elemMass.resize(size) ;
   }

   /* Temporaries should not be initialized in bulk but */
   /* this is a runnable placeholder for now */
   inline void AllocateElemTemporary(size_t size)
   {
      m_dxx.resize(size) ;
      m_dyy.resize(size) ;
      m_dzz.resize(size) ;

      m_delv_xi.resize(size) ;
      m_delv_eta.resize(size) ;
      m_delv_zeta.resize(size) ;

      m_delx_xi.resize(size) ;
      m_delx_eta.resize(size) ;
      m_delx_zeta.resize(size) ;

      m_vnew.resize(size) ;
   }

   inline void AllocateNodesets(size_t size)
   {
      m_symmX.resize(size) ;
      m_symmY.resize(size) ;
      m_symmZ.resize(size) ;
   }
   
   /**********/
   /* Access */
   /**********/

   /* Node-centered */

   inline Real_t& x(Index_t idx)    { return m_x[idx] ; }
   inline Real_t& y(Index_t idx)    { return m_y[idx] ; }
   inline Real_t& z(Index_t idx)    { return m_z[idx] ; }

   inline Real_t& xd(Index_t idx)   { return m_xd[idx] ; }
   inline Real_t& yd(Index_t idx)   { return m_yd[idx] ; }
   inline Real_t& zd(Index_t idx)   { return m_zd[idx] ; }

   inline Real_t& xdd(Index_t idx)  { return m_xdd[idx] ; }
   inline Real_t& ydd(Index_t idx)  { return m_ydd[idx] ; }
   inline Real_t& zdd(Index_t idx)  { return m_zdd[idx] ; }

   inline Real_t& fx(Index_t idx)   { return m_fx[idx] ; }
   inline Real_t& fy(Index_t idx)   { return m_fy[idx] ; }
   inline Real_t& fz(Index_t idx)   { return m_fz[idx] ; }

   inline Real_t& nodalMass(Index_t idx) { return m_nodalMass[idx] ; }

   inline Index_t&  symmX(Index_t idx) { return m_symmX[idx] ; }
   inline Index_t&  symmY(Index_t idx) { return m_symmY[idx] ; }
   inline Index_t&  symmZ(Index_t idx) { return m_symmZ[idx] ; }

   /* Element-centered */

   inline Index_t&  matElemlist(Index_t idx) { return m_matElemlist[idx] ; }
   inline Index_t*  nodelist(Index_t idx)    { return &m_nodelist[Index_t(8)*idx] ; }

   inline Index_t&  lxim(Index_t idx) { return m_lxim[idx] ; }
   inline Index_t&  lxip(Index_t idx) { return m_lxip[idx] ; }
   inline Index_t&  letam(Index_t idx) { return m_letam[idx] ; }
   inline Index_t&  letap(Index_t idx) { return m_letap[idx] ; }
   inline Index_t&  lzetam(Index_t idx) { return m_lzetam[idx] ; }
   inline Index_t&  lzetap(Index_t idx) { return m_lzetap[idx] ; }

   inline Int_t&  elemBC(Index_t idx) { return m_elemBC[idx] ; }

   inline Real_t& dxx(Index_t idx)  { return m_dxx[idx] ; }
   inline Real_t& dyy(Index_t idx)  { return m_dyy[idx] ; }
   inline Real_t& dzz(Index_t idx)  { return m_dzz[idx] ; }

   inline Real_t& delv_xi(Index_t idx)    { return m_delv_xi[idx] ; }
   inline Real_t& delv_eta(Index_t idx)   { return m_delv_eta[idx] ; }
   inline Real_t& delv_zeta(Index_t idx)  { return m_delv_zeta[idx] ; }

   inline Real_t& delx_xi(Index_t idx)    { return m_delx_xi[idx] ; }
   inline Real_t& delx_eta(Index_t idx)   { return m_delx_eta[idx] ; }
   inline Real_t& delx_zeta(Index_t idx)  { return m_delx_zeta[idx] ; }

   inline Real_t& e(Index_t idx)          { return m_e[idx] ; }

   inline Real_t& p(Index_t idx)          { return m_p[idx] ; }
   inline Real_t& q(Index_t idx)          { return m_q[idx] ; }
   inline Real_t& ql(Index_t idx)         { return m_ql[idx] ; }
   inline Real_t& qq(Index_t idx)         { return m_qq[idx] ; }

   inline Real_t& v(Index_t idx)          { return m_v[idx] ; }
   inline Real_t& volo(Index_t idx)       { return m_volo[idx] ; }
   inline Real_t& vnew(Index_t idx)       { return m_vnew[idx] ; }
   inline Real_t& delv(Index_t idx)       { return m_delv[idx] ; }
   inline Real_t& vdov(Index_t idx)       { return m_vdov[idx] ; }

   inline Real_t& arealg(Index_t idx)     { return m_arealg[idx] ; }
   
   inline Real_t& ss(Index_t idx)         { return m_ss[idx] ; }

   inline Real_t& elemMass(Index_t idx)  { return m_elemMass[idx] ; }

   /* Params */

   inline Real_t& dtfixed()              { return m_dtfixed ; }
   inline Real_t& time()                 { return m_time ; }
   inline Real_t& deltatime()            { return m_deltatime ; }
   inline Real_t& deltatimemultlb()      { return m_deltatimemultlb ; }
   inline Real_t& deltatimemultub()      { return m_deltatimemultub ; }
   inline Real_t& stoptime()             { return m_stoptime ; }

   inline Real_t& u_cut()                { return m_u_cut ; }
   inline Real_t& hgcoef()               { return m_hgcoef ; }
   inline Real_t& qstop()                { return m_qstop ; }
   inline Real_t& monoq_max_slope()      { return m_monoq_max_slope ; }
   inline Real_t& monoq_limiter_mult()   { return m_monoq_limiter_mult ; }
   inline Real_t& e_cut()                { return m_e_cut ; }
   inline Real_t& p_cut()                { return m_p_cut ; }
   inline Real_t& ss4o3()                { return m_ss4o3 ; }
   inline Real_t& q_cut()                { return m_q_cut ; }
   inline Real_t& v_cut()                { return m_v_cut ; }
   inline Real_t& qlc_monoq()            { return m_qlc_monoq ; }
   inline Real_t& qqc_monoq()            { return m_qqc_monoq ; }
   inline Real_t& qqc()                  { return m_qqc ; }
   inline Real_t& eosvmax()              { return m_eosvmax ; }
   inline Real_t& eosvmin()              { return m_eosvmin ; }
   inline Real_t& pmin()                 { return m_pmin ; }
   inline Real_t& emin()                 { return m_emin ; }
   inline Real_t& dvovmax()              { return m_dvovmax ; }
   inline Real_t& refdens()              { return m_refdens ; }

   inline Real_t& dtcourant()            { return m_dtcourant ; }
   inline Real_t& dthydro()              { return m_dthydro ; }
   inline Real_t& dtmax()                { return m_dtmax ; }

   inline Int_t&  cycle()                { return m_cycle ; }

   inline Index_t&  sizeX()              { return m_sizeX ; }
   inline Index_t&  sizeY()              { return m_sizeY ; }
   inline Index_t&  sizeZ()              { return m_sizeZ ; }
   inline Index_t&  numElem()            { return m_numElem ; }
   inline Index_t&  numNode()            { return m_numNode ; }

private:

   /******************/
   /* Implementation */
   /******************/

   /* Node-centered */

   std::vector<Real_t> m_x ;  /* coordinates */
   std::vector<Real_t> m_y ;
   std::vector<Real_t> m_z ;

   std::vector<Real_t> m_xd ; /* velocities */
   std::vector<Real_t> m_yd ;
   std::vector<Real_t> m_zd ;

   std::vector<Real_t> m_xdd ; /* accelerations */
   std::vector<Real_t> m_ydd ;
   std::vector<Real_t> m_zdd ;

   std::vector<Real_t> m_fx ;  /* forces */
   std::vector<Real_t> m_fy ;
   std::vector<Real_t> m_fz ;

   std::vector<Real_t> m_nodalMass ;  /* mass */

   std::vector<Index_t> m_symmX ;  /* symmetry plane nodesets */
   std::vector<Index_t> m_symmY ;
   std::vector<Index_t> m_symmZ ;

   /* Element-centered */

   std::vector<Index_t>  m_matElemlist ;  /* material indexset */
   std::vector<Index_t>  m_nodelist ;     /* elemToNode connectivity */

   std::vector<Index_t>  m_lxim ;  /* element connectivity across each face */
   std::vector<Index_t>  m_lxip ;
   std::vector<Index_t>  m_letam ;
   std::vector<Index_t>  m_letap ;
   std::vector<Index_t>  m_lzetam ;
   std::vector<Index_t>  m_lzetap ;

   std::vector<Int_t>    m_elemBC ;  /* symmetry/free-surface flags for each elem face */

   std::vector<Real_t> m_dxx ;  /* principal strains -- temporary */
   std::vector<Real_t> m_dyy ;
   std::vector<Real_t> m_dzz ;

   std::vector<Real_t> m_delv_xi ;    /* velocity gradient -- temporary */
   std::vector<Real_t> m_delv_eta ;
   std::vector<Real_t> m_delv_zeta ;

   std::vector<Real_t> m_delx_xi ;    /* coordinate gradient -- temporary */
   std::vector<Real_t> m_delx_eta ;
   std::vector<Real_t> m_delx_zeta ;
   
   std::vector<Real_t> m_e ;   /* energy */

   std::vector<Real_t> m_p ;   /* pressure */
   std::vector<Real_t> m_q ;   /* q */
   std::vector<Real_t> m_ql ;  /* linear term for q */
   std::vector<Real_t> m_qq ;  /* quadratic term for q */

   std::vector<Real_t> m_v ;     /* relative volume */
   std::vector<Real_t> m_volo ;  /* reference volume */
   std::vector<Real_t> m_vnew ;  /* new relative volume -- temporary */
   std::vector<Real_t> m_delv ;  /* m_vnew - m_v */
   std::vector<Real_t> m_vdov ;  /* volume derivative over volume */

   std::vector<Real_t> m_arealg ;  /* characteristic length of an element */
   
   std::vector<Real_t> m_ss ;      /* "sound speed" */

   std::vector<Real_t> m_elemMass ;  /* mass */

   /* Parameters */

   Real_t  m_dtfixed ;           /* fixed time increment */
   Real_t  m_time ;              /* current time */
   Real_t  m_deltatime ;         /* variable time increment */
   Real_t  m_deltatimemultlb ;
   Real_t  m_deltatimemultub ;
   Real_t  m_stoptime ;          /* end time for simulation */

   Real_t  m_u_cut ;             /* velocity tolerance */
   Real_t  m_hgcoef ;            /* hourglass control */
   Real_t  m_qstop ;             /* excessive q indicator */
   Real_t  m_monoq_max_slope ;
   Real_t  m_monoq_limiter_mult ;
   Real_t  m_e_cut ;             /* energy tolerance */
   Real_t  m_p_cut ;             /* pressure tolerance */
   Real_t  m_ss4o3 ;
   Real_t  m_q_cut ;             /* q tolerance */
   Real_t  m_v_cut ;             /* relative volume tolerance */
   Real_t  m_qlc_monoq ;         /* linear term coef for q */
   Real_t  m_qqc_monoq ;         /* quadratic term coef for q */
   Real_t  m_qqc ;
   Real_t  m_eosvmax ;
   Real_t  m_eosvmin ;
   Real_t  m_pmin ;              /* pressure floor */
   Real_t  m_emin ;              /* energy floor */
   Real_t  m_dvovmax ;           /* maximum allowable volume change */
   Real_t  m_refdens ;           /* reference density */

   Real_t  m_dtcourant ;         /* courant constraint */
   Real_t  m_dthydro ;           /* volume change constraint */
   Real_t  m_dtmax ;             /* maximum allowable time increment */

   Int_t   m_cycle ;             /* iteration count for simulation */

   Index_t   m_sizeX ;           /* X,Y,Z extent of this block */
   Index_t   m_sizeY ;
   Index_t   m_sizeZ ;

   Index_t   m_numElem ;         /* Elements/Nodes in this domain */
   Index_t   m_numNode ;
} mesh ;


