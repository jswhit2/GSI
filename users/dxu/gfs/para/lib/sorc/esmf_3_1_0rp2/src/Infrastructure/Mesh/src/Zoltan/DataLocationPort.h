/*
  A port that calculates where different entities need to be sent or 
  received from.
  Has not been debated on

  J. Ray, SNL, Livermore, 09/21/02
*/

#ifndef DataLocationPortSeen
#define DataLocationPortSeen

#include "cca.h"
#include "LoadBalancer.h"
#include "EntityList.h"

// namespace conversion
#include "CONV_NS.h"

namespace LoadPartitionerSpace
{
  class DataLocationPort : public virtual CONV_NS(Port)
  {

    public :

    DataLocationPort() : CONV_NS(Port)()  {}

    virtual ~DataLocationPort() {}

    /// Compute destinations
    /** Given a load-balancer and a list of off-proc entities that
	need to come to me, figure which of my entities I need to 
	send and where.
	@param A_lb : a load-balancer
	@param OffProcEntitesComingToMe : list of off-proc entites scheduled to
	                                  come here.
        @param MyEntitiesMigratingElsewhere : pointer to a list, generated by the 
	                                      component regarding this proc's 
					      entites, going elsewhere
        @return -1 : Error, else 0.					      
    */
    virtual int ComputeDestinations(LoadBalancer *A_lb, 
				    EntityList *OffProcEntitiesComingToMe,
				    EntityList **MyEntitiesMigratingElsewhere) = 0;
    
    /** Given a load-balancer and a list of my entities I need to 
	send else where, figure out the  off-proc entities that need to come to me
	and from where.
	@param A_lb : a load-balancer
	@param OffProcEntitesComingToMe : pointer to a list, generated by the 
	                                  component, of off-proc entites scheduled to
	                                  come here.
        @param MyEntitiesMigratingElsewhere : a list, provided by the 
	                                      caller, of this proc's 
					      entites, going elsewhere
        @return -1 : Error, else 0.					      
    */
    virtual int ComputeSources(LoadBalancer *A_lb, 
			       EntityList *MyEntitiesMigratingElsewhere,
			       EntityList **OffProcEntitiesComingToMe) = 0 ;

    /** Given a load-balancer, and list of objects coming to me and my objects
	going away, this method sets in motion the mechanism for packing/unpacking/
	exchanging objects. The actual work is done in another component via methods
	calls from here.
	@param MyEntitiesMigratingElsewhere : my entities going elsewhere
	@param OffProcEntitiesComingToMe : Off Proc Entities Coming To Me
	@return -1 : Error, else 0
    */
    virtual int MigrateEntities( LoadBalancer *, 
				 EntityList *MyEntitiesMigratingElsewhere,
				 EntityList *OffProcEntitiesComingToMe) = 0 ;
    
    
    /// Cleanup
    virtual void Cleanup( LoadBalancer *lb) = 0 ;
  };
};
#endif
