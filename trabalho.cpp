#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>

using namespace std;

// Declaração da struct
struct paciente{
    string senha;
    char prioridade;
    int hora;
    int min;
};

//Soma o total de todas as filas ao mesmo tempo e, se tamanho_filas > pico_lotacao, pico_lotacao assume o valor de tamanho_filas
void calcula_tamanho(queue<paciente> &vermelho, queue<paciente> &amarelo, queue<paciente> &verde, queue<paciente> &branco, int &pico_lotacao){
    int tamanho_filas; 
    tamanho_filas = vermelho.size() + amarelo.size() + verde.size() + branco.size();
    if(tamanho_filas>pico_lotacao){
        pico_lotacao=tamanho_filas;
    }
}

// Função para entrada de pacientes.
void chegada(queue<paciente> &vermelho, queue<paciente> &amarelo, queue<paciente> &verde, queue<paciente> &branco, int &pico_lotacao){
    paciente p;

    cout << "Digite a senha: ";
    cin >> p.senha;
    
    cout << "Digite a prioridade: ";
    cin >> p.prioridade;
    
    cout << "Digite a hora: ";
    cin>> p.hora;
    
    cout << "Digite os minutos: ";
    cin >> p.min;
    
    // Converte prioridade para maiúscula
    p.prioridade = toupper(p.prioridade);
    
    switch (p.prioridade){
        case 'V':
            vermelho.push(p);
            cout<<"\nPaciente adicionado com sucesso."<<endl;
            break;
        
        case 'A':
            amarelo.push(p);
            cout<<"\nPaciente adicionado com sucesso."<<endl;
            break;

        case 'D':
            verde.push(p);
            cout<<"\nPaciente adicionado com sucesso."<<endl;
            break;

        case 'B':
            branco.push(p);
            cout<<"\nPaciente adicionado com sucesso."<<endl;
            break;

        default:
            cout << "\nERRO: Prioridade inválida! Use V, A, D ou B." << endl;
            return;  
    }

    // Atualiza o pico de lotação após a chegada de um novo paciente
    calcula_tamanho(vermelho, amarelo, verde, branco, pico_lotacao);
}

/* Calcula o tempo de espera em minutos do paciente que está na frente da fila. Subtrai o horário de chegada do horário de
atendimento. Se a subtração dos minutos der negativo, significa que houve "empréstimo" de uma hora. Nesse caso, subtrai 1 da
diferença de horas e soma 60 aos minutos para ajustar corretamente. Converte tudo para minutos e, se o tempo calculado for
maior que maior_espera, atualiza maior_espera com o novo valor. */
void calcula_tempo(int &hora_atendimento, int &min_atendimento, queue<paciente> &fila, int &maior_espera){
    int tempo_min = min_atendimento - fila.front().min;
    int tempo_hora = hora_atendimento - fila.front().hora;
    if (tempo_min < 0){
        tempo_hora--;
        tempo_min += 60;
    }
    
    tempo_hora = tempo_hora * 60;

    if((tempo_hora + tempo_min) > maior_espera){
        maior_espera = tempo_hora + tempo_min;
    }
}

/* Função de atender. Recebe hora e minutos, e valida se filas estão vazias ou não, também
calculando o tempo de espera para cada paciente em cada prioridade. */
void atender (queue<paciente> &vermelho, queue<paciente> &amarelo, queue<paciente> &verde, queue<paciente> &branco, int &total_atendimento, int &maior_espera, int &total_vermelho, int &total_amarelo, int &total_verde, int &total_branco){
    int hora_atendimento, min_atendimento;

    cout << "Digite a hora: ";
    cin >> hora_atendimento;
    
    cout << "Digite os minutos: ";
    cin >> min_atendimento;

    if (vermelho.size() > 0 ){
        calcula_tempo(hora_atendimento, min_atendimento, vermelho, maior_espera);
        vermelho.pop();
        total_atendimento++;
        total_vermelho++;
        cout << "\nAtendimento realizado com sucesso." << endl;

    } else if (amarelo.size() > 0 ){
        calcula_tempo(hora_atendimento, min_atendimento, amarelo, maior_espera);
        amarelo.pop();
        total_atendimento++;
        total_amarelo++;
        cout << "\nAtendimento realizado com sucesso." << endl;

    } else if (verde.size() > 0 ){
        calcula_tempo(hora_atendimento, min_atendimento, verde, maior_espera);
        verde.pop();
        total_atendimento++;
        total_verde++;
        cout << "\nAtendimento realizado com sucesso." << endl;

    } else if (branco.size() > 0 ){
        calcula_tempo(hora_atendimento, min_atendimento, branco, maior_espera);
        branco.pop();
        total_atendimento++;
        total_branco++;
        cout << "\nAtendimento realizado com sucesso." << endl;
        
    } else {
        //formatando para aparecer a hora certa, caso contrário ficaria 14:5 ao invés de 14:05 por exemplo
        if (min_atendimento < 10) {
            cout << hora_atendimento << ":" << "0" << min_atendimento << " Sem pacientes aguardando atendimento." << endl;
        } else {
            cout << hora_atendimento << ":" << min_atendimento << " Sem pacientes aguardando atendimento." << endl;
        }
    }
}

/* Função de consulta. Printa o tamanho das filas no momento, e também o total atendido,
já gravado anteriormente. */
void consulta(queue<paciente> &vermelho, queue<paciente> &amarelo, queue<paciente> &verde, queue<paciente> &branco, int total_atendimento) {

    cout << "\nV:" << vermelho.size()
         << " A:" << amarelo.size()
         << " D:" << verde.size()
         << " B:" << branco.size()
         << " | " 
         << "Atendidos: " << total_atendimento << endl;
}

/* Função de quit. Printa o relatório final, com dados anteriormente já gravados, como
o total atendido, total por prioridade, o pico de lotação e a espera máxima em minutos. */
void quit(int &total_atendimento, int &total_vermelho, int &total_amarelo, int &total_verde, int &total_branco, int &pico_lotacao, int &maior_espera){
    cout << "\n---RELATÓRIO FINAL---" << endl
    << "Total atendidos: " << total_atendimento << endl
    << "Por prioridade: " << "V=" << total_vermelho << " A=" <<  total_amarelo << " D=" <<  total_verde << " B=" <<  total_branco
    <<   endl << "Pico de lotação: " << pico_lotacao << endl
    << "Espera máxima: " << maior_espera << " min" << endl;
}

int main(){

    // DECLARAÇÃO DE VARIÁVEIS
    queue<paciente> vermelho,amarelo,verde,branco;
    int total_atendimento = 0;
    int maior_espera = 0;
    int total_vermelho = 0, total_amarelo = 0, total_verde = 0, total_branco = 0;
    int pico_lotacao = 0;  
    char opcao;
    //

    // Loop para o menu, até que o usuário escolha a opção 'Q'.
    while (true){
        cout << endl;
        cout << "ESCOLHA UMA OPÇÃO:" << endl;
        cout << "C - CHEGADA DE UM PACIENTE." << endl;
        cout << "A - REALIZAR UM ATENDIMENTO." << endl;
        cout << "D - EXIBIR INFORMAÇÕES SOBRE O ESTADO ATUAL DA FILA." << endl;
        cout << "Q - ENCERRAR." << endl;
        cout << endl;

        cin >> opcao;
        
        // Converte para maiúscula
        opcao = toupper(opcao);

        switch (opcao){
            case 'C':
                chegada(vermelho,amarelo,verde,branco, pico_lotacao);
                break;

            case 'A':
                atender(vermelho, amarelo, verde, branco, total_atendimento, maior_espera, total_vermelho, total_amarelo, total_verde, total_branco);
                break;

            case 'D':
                consulta(vermelho,amarelo,verde,branco, total_atendimento);
                break;
            
            case 'Q':
                break;
        }

        if(opcao == 'Q'){
            break;
        }
    }

    quit(total_atendimento, total_vermelho, total_amarelo, total_verde, total_branco, pico_lotacao, maior_espera);


    return 0; 
}