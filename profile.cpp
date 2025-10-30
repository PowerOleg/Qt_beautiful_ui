#include "profile.h"

Profile::Profile(/*QWidget*/QFrame *parent)
    : /*QWidget*/QFrame{parent}
{

}
/*//    m_ui->setupUi(this);



       resize(100, 50);
       setWindowTitle("my_frame");
       QGridLayout* lCalcLayout = new QGridLayout;
       setLayout(lCalcLayout);
//       createWidgets();




//       m_hexIntegerValidator = new HexIntegerValidator(this);
//       m_ui->frameIdEdit->setValidator(m_hexIntegerValidator);
//       m_hexStringValidator = new HexStringValidator(this);
//       m_ui->payloadEdit->setValidator(m_hexStringValidator);
//       connect(m_ui->dataFrame, &QRadioButton::toggled, [this](bool set) {
//       if (set)
//           m_ui->flexibleDataRateBox->setEnabled(true);
//       });

//       auto frameIdTextChanged = [this]() {
//               const bool hasFrameId = !m_ui->frameIdEdit->text().isEmpty();
//               m_ui->sendButton->setEnabled(hasFrameId);
//               m_ui->sendButton->setToolTip(hasFrameId ? QString() : tr("Cannot send because no Frame ID was given."));
//           };*/
