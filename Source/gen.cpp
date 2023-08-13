#include "gen.h"
#include "./ui_gen.h"
int levelstart = 1;
QList<QString> type = {"Acid", "Cold", "Fire", "Thunder", "Lightning"};
QList<QString> effect = {"","","","",""};
QString text = "";
QString damage;
QString name;
QString spelltype;
int baseelement;
int dice;
gen::gen(QWidget *parent):
     QMainWindow(parent)
    , ui(new Ui::gen)
{
    ui->setupUi(this);
    ui->output->setText(text);
}
gen::~gen()
{
    delete ui;
}



void gen::on_exec_clicked()
{
effect = {
    ui->Acideff->text() +"\n",
    ui->Coldeff->text() +"\n",
    ui->Fireeff->text() +"\n",
    ui->Thundereff->text() +"\n",
    ui->Lightningeff->text() +"\n"};
levelstart = ui->level->value();
text = ui->BaseSpell->toPlainText()+"\n\n";
damage = ui->damage->text();
dice = ui->dice->value();
name = ui->name->text();
spelltype = ui->spelltype->text();
int projectile = ui->project->value();
int updice = 1;
baseelement = ui->baseelement->currentIndex();


            for(int i = 0; i<5; i++ ){
             if(ui->transmuted->isChecked()){
               text = text + "\nnew entry \""+spelltype+"_"+name+"_" + type[i] + "\"\n"
               "using \""+spelltype+"_"+name+"\"\n"
               "data \"DamageType\" \"" + type[i] + "\"\n"
               "data \"DescriptionParams\" \"DealDamage("+ QString::number(dice)+damage+"," + type[i] + ");"+QString::number(projectile)+"\"\n"+
               "data \"TooltipDamageList\" \"DealDamage("+QString::number(dice*projectile)+damage+"," + type[i] + ")\"\n"
               + effect[i] +
               "data \"SpellFail\" \"None\"\n"+
               "data \"SpellSuccess\" \"DealDamage("+QString::number(dice)+damage+"," + type[i] + ",Magical)\"\n"+
               "data \"SpellContainerID\" \""+spelltype+"_"+name+"\"\n";
                    if(ui->uptype->currentIndex()==0)
                        text = text +"data \"TooltipUpcastDescription\" \"f59d4740-0a34-49ff-90e1-cbe0a668f370\"\n";
                    if(ui->uptype->currentIndex()==1)
                        text = text +"data \"TooltipUpcastDescription\" \"66388a6f-44dd-4c9f-a9e7-910c50e70755\"\n";
                    if(ui->baseelement->currentIndex()!=i)
                        text = text + "data \"UseCosts\" \"SpellSlotsGroup:1:1:"+QString::number(levelstart)+";ActionPoint:1;SorceryPoint:1;Transmutation_Charge:1\"\n";
             }
        if(ui->upcast->isChecked()) {
            for(int level = levelstart+1; level<7 ;level++){
                updice =level-levelstart;
                text = text + "\nnew entry \""+spelltype+"_"+name+"_" + type[i] + "_" + QString::number(level) + "\"\n"+
                "using \""+spelltype+"_"+name+"_" + type[i] + "\"\n"+
                "data \"DescriptionParams\" \"DealDamage("+ QString::number(dice)+damage+"," + type[i] + ");" + QString::number(projectile+updice) + "\"\n"+
                       "data \"TooltipDamageList\" \"DealDamage(" + QString::number((projectile+updice)*dice) +damage+"," + type[i] + ")\"\n"+
                "data \"RootSpellID\" \"Projectile_"+name+"_" + type[i] + "\"\n"+
                "data \"PowerLevel\" \"" + QString::number(level) + "\"\n";
                if(ui->baseelement->currentIndex()==i)
                    text = text + "data \"UseCosts\" \"SpellSlotsGroup:1:1:"+QString::number(level)+";ActionPoint:1\"\n";
                else
                    text = text + "data \"UseCosts\" \"SpellSlotsGroup:1:1:"+QString::number(level)+";ActionPoint:1;SorceryPoint:1;Transmutation_Charge:1\"\n";
                if(ui->uptype->currentIndex()==0)
                   text = text + "data \"AmountOfTargets\" \"" + QString::number(projectile+updice) + "\"\n";
                if(ui->uptype->currentIndex()==1){
                    text = text +"data \"SpellSuccess\" \"DealDamage("+QString::number(dice+updice)+damage+"," + type[i] + ",Magical)\"\n"
                        "data \"TooltipUpcastDescriptionParams\" \"DealDamage(1"+damage+"," + type[i] + ")\"\n";
                }

            }
        }



    }
            ui->debug->setText(QString::number(ui->uptype->currentIndex()));
    ui->output->setText(text);
}

void gen::on_upcast_clicked()
{
    if(!ui->upcast->isChecked())
        ui->uptype->setCurrentIndex(2);

      ui->uptype->setEnabled(ui->upcast->isChecked());


}
