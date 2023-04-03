#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"
#include "shipChooser.h"


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
    wex::label &lbCarrier1;
    wex::editbox &edCarrier1;
    wex::label &lbCarrier2;
    wex::editbox &edCarrier2;
    wex::label &lbCarrier3;
    wex::editbox &edCarrier3;
    wex::label &lbCarrier4;
    wex::editbox &edCarrier4;
    wex::label &lbCarrier5;
    wex::editbox &edCarrier5;

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
};

class cShipChooser
{
    public:
    std::string Authorization;
};

cShipChooser theShipChooser;

cGUI::cGUI()
    : cStarterGUI(
          "ShipChooser",
          {50, 50, 1000, 600}),
      lbCarriers(wex::maker::make<wex::label>(fm)),
      plPackage(wex::maker::make<wex::panel>(fm)),
      bnBatch(wex::maker::make<wex::button>(plPackage)),
      gpPackage(wex::maker::make<wex::groupbox>(plPackage)),
      lbWeight(wex::maker::make<wex::label>(plPackage)),
      edWeight(wex::maker::make<wex::editbox>(plPackage)),
      lbLength(wex::maker::make<wex::label>(plPackage)),
      edLength(wex::maker::make<wex::editbox>(plPackage)),
      lbWidth(wex::maker::make<wex::label>(plPackage)),
      edWidth(wex::maker::make<wex::editbox>(plPackage)),
      lbHeight(wex::maker::make<wex::label>(plPackage)),
      edHeight(wex::maker::make<wex::editbox>(plPackage)),
      lbSrc(wex::maker::make<wex::label>(plPackage)),
      edSrc(wex::maker::make<wex::editbox>(plPackage)),
      lbDst(wex::maker::make<wex::label>(plPackage)),
      edDst(wex::maker::make<wex::editbox>(plPackage)),
      rbCommercial(wex::maker::make<wex::radiobutton>(plPackage)),
      rbResidential(wex::maker::make<wex::radiobutton>(plPackage)),

      plCarrier(wex::maker::make<wex::panel>(fm)),
      gpCarrier(wex::maker::make<wex::groupbox>(plCarrier)),

      lbCarrier1(wex::maker::make<wex::label>(plCarrier)),
      edCarrier1(wex::maker::make<wex::editbox>(plCarrier)),
      bnAuthorization(wex::maker::make<wex::button>(plCarrier)),
      bnCarriers(wex::maker::make<wex::button>(plCarrier)),
      lbCarrier2(wex::maker::make<wex::label>(plCarrier)),
      edCarrier2(wex::maker::make<wex::editbox>(plCarrier)),
      lbCarrier3(wex::maker::make<wex::label>(plCarrier)),
      edCarrier3(wex::maker::make<wex::editbox>(plCarrier)),
      lbCarrier4(wex::maker::make<wex::label>(plCarrier)),
      edCarrier4(wex::maker::make<wex::editbox>(plCarrier)),
      lbCarrier5(wex::maker::make<wex::label>(plCarrier)),
      edCarrier5(wex::maker::make<wex::editbox>(plCarrier)),

      plChoice(wex::maker::make<wex::panel>(fm)),
      gpChoice(wex::maker::make<wex::groupbox>(plChoice)),
      bnChoose(wex::maker::make<wex::button>(plChoice)),
      lbChoice(wex::maker::make<wex::label>(plChoice)),
      edCost(wex::maker::make<wex::editbox>(plChoice)),
      edTime(wex::maker::make<wex::editbox>(plChoice)),

      plLogic(wex::maker::make<wex::panel>(fm)),
      gpLogic(wex::maker::make<wex::groupbox>(plLogic)),
      lbLogic(wex::maker::make<wex::label>(plLogic))

{

    constructPackagePanel(10, 20);
    constructCarrierPanel(250, 20);
    constructChoicePanel(500, 20);
    constructLogicPanel(750, 20);

    show();
    run();
}
void cGUI::constructPackagePanel(int x, int y)
{
    plPackage.move(x, y, 200, 500);
    gpPackage.move({10, 10, 190, 490});
    gpPackage.text("Package");

    bnBatch.move(50, 50, 70, 30);
    bnBatch.text("Batch");

    y = 90;
    int lbw = 80;
    int edx = lbw + 30;
    lbWeight.move(20, y, lbw, 30);
    lbWeight.text("Weight");
    edWeight.move(edx, y, 50, 30);
    edWeight.text("");

    y += 50;
    lbLength.move(20, y, lbw, 30);
    lbLength.text("Length");
    edLength.move(edx, y, 50, 30);
    edLength.text("");

    y += 50;
    lbWidth.move(20, y, lbw, 30);
    lbWidth.text("Width");
    edWidth.move(edx, y, 50, 30);
    edWidth.text("");

    y += 50;
    lbHeight.move(20, y, lbw, 30);
    lbHeight.text("Height");
    edHeight.move(edx, y, 50, 30);
    edHeight.text("");

    y += 50;
    lbSrc.move(20, y, lbw, 30);
    lbSrc.text("Source ZIP");
    edSrc.move(edx, y, 50, 30);
    edSrc.text("");

    y += 50;
    lbDst.move(20, y, lbw, 30);
    lbDst.text("Dest ZIP");
    edDst.move(edx, y, 50, 30);
    edDst.text("");

    y += 50;
    rbCommercial.move(20, y, 120, 30);
    rbCommercial.text("Commercial");
    y += 40;
    rbResidential.move(20, y, 120, 20);
    rbResidential.text("Residential");
}
void cGUI::constructCarrierPanel(int x, int y)
{
    vCarrier.clear();
    vCarrier.emplace_back("FedEX", "fedex",
     "FedEx Ground®","fedex_ground");
    vCarrier.emplace_back("FedEX", "fedex",
     "FedEx Home Delivery®","fedex_home_delivery");

    plCarrier.move(x, y, 200, 400);
    gpCarrier.move({10, 10, 190, 390});
    gpCarrier.text("Carriers");

    y = 40;
    bnAuthorization.move(50, y, 100, 30);
    bnAuthorization.text("Authorization");

    y += 40;
    bnCarriers.move(50, y, 70, 30);
    bnCarriers.text("Update");

    int lbw = 80;
    int edx = lbw + 30;
    y += 50;
    lbCarrier1.move(15, y, lbw, 30);
    lbCarrier1.text(vCarrier[0].text());
    edCarrier1.move(edx, y, 50, 30);
    edCarrier1.text(std::to_string(vCarrier[0].myFactorWeight));

    y += 50;
    lbCarrier2.move(15, y, lbw, 30);
    lbCarrier2.text(vCarrier[1].text());
    edCarrier2.move(edx, y, 50, 30);
    edCarrier2.text(std::to_string(vCarrier[1].myFactorWeight));
    y += 50;
}

void cGUI::constructChoicePanel(int x, int y)
{
    plChoice.move(x, y, 200, 400);
    gpChoice.move({10, 10, 190, 390});
    gpChoice.text("Choice");

    y = 50;
    bnChoose.move(50, y, 70, 30);
    bnChoose.text("CHOOSE");
    bnChoose.events().click(
        [this]
        {
            choose();
        });

    y += 50;
    lbChoice.move(20, y, 100, 200);
    lbChoice.text("Carrier: UPS \n\n\nCost: 20 \n\n\nTime: 2");
    y += 50;
    edCost.move(120, y, 70, 30);
    edCost.text(" 1");
    y += 50;
    edTime.move(120, y, 70, 30);
    edTime.text(" 1");
}
void cGUI::constructLogicPanel(int x, int y)
{
    plLogic.move(x, y, 200, 400);
    gpLogic.move({10, 10, 190, 390});
    gpLogic.text("Logic");
    lbLogic.move(20, 60, 170, 300);
    lbLogic.text("Maximize:\n\n"
                 "Carrier x Carrier Weight\n"
                 " - Cost x Cost Weight\n"
                 " - Time x Time Weight");
}

void cGUI::choose()
{
    cPackage package;
    package.myWeight = atof(edWeight.text().c_str());

    for (auto &C : vCarrier)
    {
        float cost = C.cost(package);
    }
}

std::string cCarrier::text() const
{
    return myCarrierName + "/" + myServiceName;
}

float cCarrier::cost(const cPackage &package)
{
    return 1;
}

std::string cCarrier::reqRateText()
{
    // https://www.shipstation.com/docs/api/shipments/get-rates/

    std::stringstream ss;
    ss << "POST /shipments/getrates HTTP/1.1\n"
          "Host: ssapi.shipstation.com\n"
          "Authorization:";
    ss << theShipChooser.Authorization + "\n";
    ss << "Content-Type: application/json\n"
        "{\n"
        "\"carrierCode\":" + myCarrierCode + ",\n";
        "";
    return ss.str();

}

main()
{
    cGUI theGUI;
    return 0;
}
