clear

%system('outputcopy.txt')
%system('cp output.out outputcopy.txt')
system('./main')
%system('cp output.out outputcopy.txt')

%{
fichier='output1.out';
data=load(fichier);
x1=data(:,1);
psi1=data(:,2);
fichier2='output2.out';
data=load(fichier2);
x2=data(:,1);
psi2=data(:,2);
fichier3='output3.out';
data=load(fichier3);
x3=data(:,1);
psi3=data(:,2);
%}
fichier='output.out';
data=load(fichier);
x=data(:,1);
psi=data(:,2);

%data = load('output_energy.out');
%E = data(end,1);
