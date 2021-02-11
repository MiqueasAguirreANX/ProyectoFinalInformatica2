#include <QApplication>
#include <QPushButton>
#include "agregar_datos.h"
#include "consultas.h"
#include "estadisticas.h"


class AgregarDatos;
class Estadisticas;
class Consultas;

class Menu : public QWidget {

    Q_OBJECT

    private:

        // Botones de navegacion
        QPushButton *btnAgregarDatos;
        QPushButton *btnEstadisticas;
        QPushButton *btnConsultas;

        // Referencias a las ventanas
        AgregarDatos *agregarDatos;
        Estadisticas *estadisticas;
        Consultas *consultas;

    public:

        Menu(QWidget *parent = 0);

    public slots:

        void MostrarAgregarDatos();
        void MostrarEstadisticas();
        void MostrarConsultas();
        void EsconderAgregarDatos();
        void EsconderEstadisticas();
        void EsconderConsultas();

};
