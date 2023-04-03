class cPackage
{
public:
    float myWeight;
    float myLength;
    float myWidth;
    float myHeight;
    std::string mySrc;
    std::string myDst;
    bool myfResidential;
};

class cCarrier
{
public:
    std::string myCarrierName;
    std::string myServiceName;
    std::string myCarrierCode;
    std::string myServiceCode;
    float myFactorWeight;

    cCarrier(
        const std::string &Carriername,
        const std::string &Carriercode,
        const std::string &Servicename,
        const std::string &Servicecode)
        : myCarrierName(Carriername),
          myCarrierCode(Carriercode),
          myServiceName(Servicename ),
          myServiceCode(Servicecode ),
          myFactorWeight(1)
    {
    }

    std::string text() const;
    float cost(const cPackage &package);

private:
    std::string reqRateText();
};