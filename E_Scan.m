repertoire = './';
executable = 'main';
input = 'Configuration.in ';
nsimul = 10;
E0 = linspace(-2,50,nsimul);
paramstr = 'E0'
param = E0;
output = cell(1,nsimul);
for i = 1:nsimul
    output{i} = [paramstr, '=', num2str(param(i)), '.out'];
    cmd = sprintf('%s%s %s %s=%.15g output=%s', repertoire, executable, input, paramstr, param(i), output{i})
    disp(cmd)
    %system(cmd);
end

figure
for i=[1 2 4 6 9]
    data = load(output{i});
    x = data(:,1);
    psi = data(:,2);
    pl = plot(x,psi,'DisplayName',num2str(i));
    nice_plot(pl);
    hold on
end
legend
xlabel('x')
ylabel('Wave functions')

points = linspace(-2,-1,10000);
values = 1e-50*1^6*(1^6./(points+2).^12-1./(points+2).^6)
figure
pl = plot(points,values);
nice_plot(pl)