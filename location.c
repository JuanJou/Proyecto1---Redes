char* loc_ntoa (const u_char *binary)
{


        static char tmpbuf[255*3];

        register char *cp;
        register const u_char *rcp;

        int latdeg, latmin, latsec, latsecfrac;
        int longdeg, longmin, longsec, longsecfrac;
        char northsouth, eastwest;
        int altmeters, altfrac, altsign;

        const int referencealt = 100000 * 100;

        int32_t latval, longval, altval;
        u_int32_t templ;
        u_int8_t sizeval, hpval, vpval, versionval;

        char *sizestr, *hpstr, *vpstr;

        rcp = binary;
        cp = tmpbuf;

        versionval = *rcp++;

        if (versionval) {
                sprintf(cp,"; error: unknown LOC RR version");
                return (cp);
        }

        sizeval = *rcp++;

        hpval = *rcp++;
        vpval = *rcp++;

        GETLONG(templ,rcp);
        latval = (templ - ((unsigned)1<<31));

        GETLONG(templ,rcp);
        longval = (templ - ((unsigned)1<<31));

        GETLONG(templ,rcp);
        if (templ < referencealt) { /* below WGS 84 spheroid */
                altval = referencealt - templ;
                altsign = -1;
        } else {
                altval = templ - referencealt;
                altsign = 1;
        }

        if (latval < 0) {
                northsouth = 'S';
                latval = -latval;
        }
        else
                northsouth = 'N';

        latsecfrac = latval % 1000;
        latval = latval / 1000;
        latsec = latval % 60;
        latval = latval / 60;
        latmin = latval % 60;
        latval = latval / 60;
        latdeg = latval;

        if (longval < 0) {
                eastwest = 'W';
                longval = -longval;
        }
        else
                eastwest = 'E';

        longsecfrac = longval % 1000;
        longval = longval / 1000;
        longsec = longval % 60;
        longval = longval / 60;
        longmin = longval % 60;
        longval = longval / 60;
        longdeg = longval;

        altfrac = altval % 100;
        altmeters = (altval / 100) * altsign;

        sizestr = savestr(precsize_ntoa(sizeval));
        hpstr = savestr(precsize_ntoa(hpval));
        vpstr = savestr(precsize_ntoa(vpval));

        sprintf(cp,
                "%d %.2d %.2d.%.3d %c %d %.2d %.2d.%.3d %c %d.%.2dm
                %sm %sm %sm",
                latdeg, latmin, latsec, latsecfrac, northsouth,
                longdeg, longmin, longsec, longsecfrac, eastwest,
                altmeters, altfrac, sizestr, hpstr, vpstr);

        free(sizestr);
        free(hpstr);
        free(vpstr);

        return (cp);
}
















