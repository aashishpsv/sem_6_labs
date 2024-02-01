class human:
    species="h.sapiens"

    def __init__(self,name):
     self.name = name 
     self._age=0
    def say(self,msg):
     print("{name}: {message}".format(name=self.name, message=msg))
    def sing(self): 
     return 'yo... yo... microphone check... one two... one two...'
    def get_species(cls):
      return cls.species
    def grunt():
      return "*grunt*"
    def age(self): 
      return self._age
    def age(self,age):
      self._age = age
    def age(self):
      del self._age
    
if __name__=='__main__':
    i=human(name="lan")
    i.say("hi")
    j = human("Joel") 
    j.say("hello") 
    i.say(i.get_species())
    human.species = "H. neanderthalensis"
    i.say(i.get_species()) # => "Ian: H. neanderthalensis"
    j.say(j.get_species()) 
    print(human.grunt()) 
   # print(i.grunt())
    i.age = 42 
    i.say(i.age) # => "Ian: 42"
    j.say(j.age) # => "Joel: 0" 
    del i.age
