import java.util.Date;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

public class Main {
    public static void main(String[] args) {
        
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("TestJPAPU");

        EntityManager em = emf.createEntityManager();


        Email email = new Email();
        
        email.setSubject("Subject");
        email.setSender("Sender");
        email.setTags("Tag1");
        email.setTextpreview("Textpreview");
        email.setReceived(new Date());
        email.setArchived(new Date());
        email.setCreated(new Date());
        email.setHash("sdfsdfdsf");

        em.getTransaction().begin();

        em.persist(email);
        
        em.getTransaction().commit();

        System.out.println("ID: " + email.getId());
        
        em.close();
        emf.close();

    }
}

