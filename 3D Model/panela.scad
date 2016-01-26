alturaBuraco = 51;
larguraBuraco = 96;

larguraInternaTampa = 105;
alturaInternaTampa = 61;
ProfundidadeInternaTampa = 35;
espessuraParedes = 1.5;

assembly();


module assembly(){
    case();    
    translate([-24,0,0]) placa();
    suportePanela();
    color([0.2,0.4,0.6]) tampa();
    color([0.5,0.2,0.9]) translate([-2.8,5,7]) rotate([90,0,0])  button();
    color([0.5,0.2,0.9]) translate([-2.8,13,7])  button();
    color([0.5,0.2,0.9]) translate([-2.8,22,10])  button();
    color([0.5,0.2,0.9]) translate([-2.8,22,3])  button();
    color([0.5,0.2,0.9]) translate([-2.8,31,7])  button();
    
}

module furoParafuso(di){
    translate([0,0,di/2]) rotate([90,0,0]) cylinder(d = di, h = 10, $fn = 30);
}

module suportePanela(){
  difference(){
  translate([-ProfundidadeInternaTampa - 20,0.5,0.5]) cube([30, larguraInternaTampa - 1, alturaInternaTampa - 1]);
    
  translate([-165,54,-1.5]) cylinder(d = 260.4, h = alturaInternaTampa + espessuraParedes * 2, $fn = 50)  ;
  translate([-ProfundidadeInternaTampa + 4,10,10])furoParafuso(2.6);
  translate([-ProfundidadeInternaTampa + 4,10,alturaInternaTampa - 13])furoParafuso(2.6);
  translate([-ProfundidadeInternaTampa + 4,larguraInternaTampa,10])furoParafuso(2.6);
  translate([-ProfundidadeInternaTampa + 4,larguraInternaTampa,alturaInternaTampa - 13])furoParafuso(2.6);
      
      translate([-ProfundidadeInternaTampa - 10,20,alturaInternaTampa/2]) rotate([0,90,0]) cylinder(d = 3, h = 20, $fn = 30);
  
    translate([-ProfundidadeInternaTampa - 10,larguraInternaTampa - 21.5,alturaInternaTampa/2]) rotate([0,90,0]) cylinder(d = 3, h = 20, $fn = 30);
  
  translate([-ProfundidadeInternaTampa - 10,larguraInternaTampa/2,alturaInternaTampa/2]) rotate([0,90,0]) cylinder(d = 16, h = 20, $fn = 30);
  }
  
  
}


module placa(){
    color([0.2,0.2,0.2]) translate([0,0,0]) cube([16, 80, 58]);
    translate([18,0,14]){
        color([0.2,0.5,0.8]) translate([0,0,0]) cube([2,80,36]) ;
        color([0.7,0.7,0.7]) translate([2,4,4]) cube([6,71,26]) ;
    }
    translate([16,2,0]){
        translate([0,0,4]) pushbutton();
        translate([0,8,4]) pushbutton();
        translate([0,17,0]) pushbutton();
        translate([0,17,7]) pushbutton();
        translate([0,26,4]) pushbutton();
        translate([0,34,4]) pushbutton();
    }
    translate([16, 3.5, 54]){
        color([0.1,0.4,0.9]) translate([0,0,0]) cube([10,9,4]) ;
        color([0.3,0.3,0.3]) translate([10,1,3]) rotate([0,90,0]) cylinder(d = 2, h = 1, $fn = 30) ;
    }
}

module pushbutton(){
    color([0.2,0.8,0.3]) cube([3,6,6]);
    color([0.1,0.1,0.1]) translate([3,3,3]) rotate([0,90,0]) cylinder(d = 3, h = 2, $fn = 30) ;
}

module button(){
    translate([2.5,0,0]) rotate([0,90,0])  scale([0.72,1.22,1]) cylinder(d = 6, h = 3, $fn = 30);
    rotate([0,90,0])  scale([1,1.5,1]) cylinder(d = 6, h = 2.6, $fn = 30);
}

module tampa(){
    translate([0, -espessuraParedes, -espessuraParedes])  difference(){
    cube([espessuraParedes, larguraInternaTampa + espessuraParedes * 2, alturaInternaTampa + espessuraParedes * 2]);
    
        translate([-0.5,4.5,18.5]) cube([3,73,28]);
        
        translate([-0.5,4.5,55]) cube([2,10,5]);
        translate([-0.5,6.5,8.5]) rotate([0,90,0]) scale([1.3,0.8,1]) cylinder(d = 6, h = 2, $fn = 30);
        translate([-0.5,14.5,8.5]) rotate([0,90,0]) scale([0.8,1.3,1]) cylinder(d = 6, h = 2, $fn = 30);
        translate([-0.5,23.5,11.5]) rotate([0,90,0]) scale([0.8,1.3,1]) cylinder(d = 6, h = 2, $fn = 30);
        translate([-0.5,23.5,4.5]) rotate([0,90,0]) scale([0.8,1.3,1]) cylinder(d = 6, h = 2, $fn = 30);
        translate([-0.5,32.5,8.5]) rotate([0,90,0])  scale([0.8,1.3,1]) cylinder(d = 6, h = 2, $fn = 30);
    }
    
}

module case(){
    difference(){
    translate([-ProfundidadeInternaTampa, -espessuraParedes, -espessuraParedes]) cube([ProfundidadeInternaTampa, larguraInternaTampa + espessuraParedes * 2, alturaInternaTampa + espessuraParedes * 2]);
    
    translate([-ProfundidadeInternaTampa - 0.5,0,0]) cube([ProfundidadeInternaTampa + 1, larguraInternaTampa, alturaInternaTampa]);
        
     translate([-ProfundidadeInternaTampa + 4,5,10])furoParafuso(3);
  translate([-ProfundidadeInternaTampa + 4,5,alturaInternaTampa - 13])furoParafuso(3);
  translate([-ProfundidadeInternaTampa + 4,larguraInternaTampa + 5,10])furoParafuso(3);
  translate([-ProfundidadeInternaTampa + 4,larguraInternaTampa + 5,alturaInternaTampa - 13])furoParafuso(3);
        
    }
    translate([-24,30,58.3]) cube([24,20,3]);
    translate([-15,80,0]) cube([15,2,alturaInternaTampa]);
    
   
    
}

