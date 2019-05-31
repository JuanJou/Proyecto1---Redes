/*3.4.1. A RDATA format

    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ADDRESS                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

where:

ADDRESS         A 32 bit Internet address.*/


struct A_RDATA* readARecord(unsigned char** reader) {
	struct A_RDATA* aRecord = malloc(sizeof(struct A_RDATA));
	aRecord->ip=(**reader);
	*reader += sizeof(struct A_RDATA);
	return aRecord;
}

/*MX RDATA format

    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                  PREFERENCE                   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    /                   EXCHANGE                    /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

where:

PREFERENCE      A 16 bit integer which specifies the preference given to
                this RR among others at the same owner.  Lower values
                are preferred.

EXCHANGE        A <domain-name> which specifies a host willing to act as
                a mail exchange for the owner name.
                */
struct MX_RDATA* readMXRecord(unsigned char** reader) {
	struct MX_RDATA* mxRecord = malloc(sizeof(struct MX_RDATA));
	mxRecord->preference = (**reader);
	*reader += 2;
	mxRecord -> exchange = (**reader);
	*reader += sizeof(char*);
	return mxRecord;
} 

/*
3.3.11. NS RDATA format

    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    /                   NSDNAME                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

where:

NSDNAME         A <domain-name> which specifies a host which should be
                authoritative for the specified class and domain.*/

struct NS_RDATA* readNSRecord(unsigned char** reader) {
	struct NS_RDATA* nsRecord = malloc(sizeof(char[16]));
	nsRecord -> nsdame = **reader;
	return nsRecord;
}

/*SOA RDATA format

    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    /                     MNAME                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    /                     RNAME                     /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    SERIAL                     |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    REFRESH                    |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     RETRY                     |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    EXPIRE                     |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    MINIMUM                    |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

where:

MNAME           The <domain-name> of the name server that was the
                original or primary source of data for this zone.

RNAME           A <domain-name> which specifies the mailbox of the
                person responsible for this zone.

SERIAL          The unsigned 32 bit version number of the original copy
                of the zone.  Zone transfers preserve this value.  This
                value wraps and should be compared using sequence space
                arithmetic.

REFRESH         A 32 bit time interval before the zone should be
                refreshed.

RETRY           A 32 bit time interval that should elapse before a
                failed refresh should be retried.

EXPIRE          A 32 bit time value that specifies the upper limit on
                the time interval that can elapse before the zone is no
                longer authoritative.

MINIMUM         The unsigned 32 bit minimum TTL field that should be
                exported with any RR from this zone.*/

struct SOA_RDATA* readSOARecord(char** reader) {
	struct SOA_RDATA* soaRecord = malloc(sizeof(struct SOA_RDATA));

}
