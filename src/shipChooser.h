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
        const std::string &Servicecode);

    std::string text() const;
    float cost(const cPackage &package);

private:
    std::string reqRateText();
};
class cGUI : public cStarterGUI
{
public:
    cGUI();

private:
    wex::label &lbCarriers;

    wex::panel &plPackage;
    wex::groupbox &gpPackage;
    wex::button &bnBatch;
    wex::label &lbWeight;
    wex::editbox &edWeight;
    wex::label &lbLength;
    wex::editbox &edLength;
    wex::label &lbWidth;
    wex::editbox &edWidth;
    wex::label &lbHeight;
    wex::editbox &edHeight;
    wex::label &lbSrc;
    wex::editbox &edSrc;
    wex::label &lbDst;
    wex::editbox &edDst;
    wex::radiobutton &rbCommercial;
    wex::radiobutton &rbResidential;

    wex::panel &plCarrier;
    wex::groupbox &gpCarrier;
    wex::button &bnAuthorization;
    wex::button &bnCarriers;
    wex::propertyGrid &pgCarrier;

    wex::panel &plChoice;
    wex::groupbox &gpChoice;
    wex::editbox &edCost;
    wex::editbox &edTime;
    wex::button &bnChoose;

    wex::panel &plLogic;
    wex::groupbox &gpLogic;
    wex::label &lbLogic;

    wex::label &lbChoice;

    std::vector<cCarrier> vCarrier;

    void constructCarrierPanel(int x, int y);
    void constructPackagePanel(int x, int y);
    void constructChoicePanel(int x, int y);
    void constructLogicPanel(int x, int y);

    void choose();
    void CarrierUpdate();
    void Authorization();
};

class cShipChooser
{
public:
    std::string Authorization;
};